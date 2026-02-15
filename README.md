# MINISHELL

## Overview
MINISHELL is a simple shell implementation that aims to replicate the functionality of standard Unix shells. It supports various shell commands, job control, and basic scripting functionality.

## Features
- Support for built-in commands (e.g., `cd`, `exit`, `echo`)
- Execute external commands with arguments
- Support for piping and redirection (i.e., `|`, `>`, `<`)
- Environment variable management
- Job control, including foreground and background processes
- Basic scripting capabilities with support for command substitution

## Requirements
To successfully build and run MINISHELL, you will need:
- A Unix-like environment (Linux/macOS)
- GCC (GNU Compiler Collection) or Clang installed
- Make utility to build the project

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/L7AJMAHMOUD/MINISHELL.git
   cd MINISHELL
   ```
2. Build the project:
   ```bash
   make
   ```

## Usage
To start the MINISHELL, run:
```bash
./minishell
```

You can execute commands like:
```bash
$ echo Hello, World!
$ ls -l
$ cd my_directory
```

## Examples
- Running a simple command:
  ```bash
  $ ls
  file1.txt  file2.txt
  ```
- Piping between commands:
  ```bash
  $ ls | grep file
  ```
- Using redirection:
  ```bash
  $ echo "Hello World!" > output.txt
  ```

## Contributing
Contributions to MINISHELL are welcome! Please fork the repository and submit a pull request with your changes.

## License
This project is licensed under the MIT License.