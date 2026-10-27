# Minishell

A small Unix shell written in C, with GNU Readline for interactive input.
It runs external programs, manages environment variables, and supports pipelines
and standard input/output redirection.

## Build

Requirements:

- A Unix-like system with a C compiler and Make.
- GNU Readline headers and library (`libreadline-dev` on Debian/Ubuntu).
- Python 3 and Bash for tests; Clang for sanitizer checks.

```sh
make
./minishell
```

The build enables `-Wall -Wextra -Werror`. Object files and dependency files stay
in `build/`; editing a header rebuilds its dependents automatically.

## Usage

Start `./minishell` for an interactive prompt, or supply commands through stdin:

```sh
printf 'echo hello\npwd\n' | ./minishell
./minishell < commands.txt
./minishell --help
./minishell --version
```

Examples to enter at the prompt:

```sh
export GREETING="hello world"
echo "$GREETING"
printf '%s\n' orange apple | sort
pwd > location.txt
cat < location.txt
echo another-line >> location.txt
cat << EOF
Hello, $USER
EOF
```

Supported behavior:

- Builtins: `echo` (including `-n`), `cd` (including `cd -`), `pwd`, `export`,
  `unset`, `env` without arguments, and `exit`.
- External executables, absolute/relative paths, and `PATH` lookup, including
  empty path components for the current directory.
- Single and double quotes, `$NAME`, `$?`, and unquoted variable field splitting
  on spaces, tabs, and newlines.
- Concurrent pipelines, with the status of the final command.
- `<`, `>`, `>>`, and `<<`; quoted heredoc delimiters disable expansion.
  Heredoc storage uses private temporary files that are immediately unlinked.
- Ctrl-C cancels input or interrupts foreground commands; Ctrl-D exits at an
  empty prompt. Interactive history and right-arrow history suggestions use
  `.minishell_history` in the working directory. Batch mode writes no history.

`exit` without an argument preserves the last status. Numeric arguments wrap to
0–255. Invalid numbers exit with status 2; excess arguments report status 1 and
keep the shell running. Unknown commands return 127, and commands that cannot
be executed return 126.

## Scope

This is an educational shell, not a complete Bash or POSIX shell. It does not
implement job control/background jobs, logical operators (`&&`, `||`), semicolon
lists, subshells, command substitution, globbing, backslash escapes, multiline
quoted commands, shell comments, assignment prefixes, `${...}` expansion, or
numbered file-descriptor redirections such as `2>`. Use one command or pipeline
per input line. The CLI accepts stdin input, `--help`, and `--version`; it does
not accept `-c` or a script filename argument.

## Development and validation

```sh
make test       # integration tests, including a real pseudo-terminal
make sanitize   # AddressSanitizer, UndefinedBehaviorSanitizer, leak detection
make format     # format C sources using clang-format
make clean      # remove build artifacts
make fclean     # also remove executables
make re         # clean rebuild, safe with parallel make
```

Tests run in temporary directories and check output, errors, and exit status.
They compare supported behavior against Bash, with explicit assertions for
error policies that vary between Bash versions. Coverage includes quoting,
expansion, builtins, executable lookup, permissions, pipelines, redirections,
heredocs, repeated commands, syntax errors, and interactive signals/EOF.
Sanitizer binaries use a separate build directory. GitHub Actions runs the suite
with GCC and Clang and performs sanitizer checks on Linux.

Source layout:

| Directory | Responsibility |
| --- | --- |
| `src/core` | Input loop, environment initialization, history |
| `src/parsing` | Validation, tokenization, expansion, command cleanup |
| `src/builtins` | Builtin commands and environment updates |
| `src/execution` | Executable lookup, pipelines, redirections |
| `src/heredoc` | Heredoc collection and temporary storage |
| `src/signals` | Interactive signal handling |
| `src/utils` | Shared string and process helpers |
| `tests` | Python integration suite |

Original project by Abderrahman Karam (`abkaram`) and Mahmoud En-Najy (`maen-naj`).
