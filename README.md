# MINISHELL

## Project Overview
MINISHELL is a simple UNIX shell implementation that serves as a project to learn about system-level programming, processes, and the underlying architecture of shell commands. The goal is to create a functional shell that can execute user commands, manage processes, and handle various functionalities typically found in a UNIX shell.

## Features
- **Command Execution**: Execute simple shell commands and manage processes.
- **Built-in Commands**: Support for built-in commands like `cd`, `exit`, and `echo`.
- **Environment Variables**: Access and manipulate environment variables.
- **Input/Output Redirection**: Redirect input and output using `>` and `<` operators.
- **Pipelines**: Support for command pipelines with use of `|` operator.

## Installation
To install MINISHELL, clone the repository and build the project using the following commands:

```bash
git clone https://github.com/L7AJMAHMOUD/MINISHELL.git
cd MINISHELL
make
```

Make sure that you have all the necessary dependencies installed including `gcc` and `make`.

## Usage
Run the shell by executing the following command in the terminal:

```bash
./minishell
```

You can start typing your commands after the shell prompt.

## Project Structure
The project is organized as follows:

```
MINISHELL/
├── src/
│   ├── main.c        # Entry point of the shell
│   ├── command.c     # Command execution logic
│   ├── builtin.c     # Built-in command implementations
│   └── ...           # Other source files
├── inc/
│   ├── minishell.h   # Header file with function declarations
│   └── ...           # Other headers
└── Makefile          # Build script
```

## Documentation
For detailed documentation, refer to the `docs/` folder. It contains information on the design decisions, architecture, and advanced usage of the shell features.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Author
This project is maintained by Karamu-ser.