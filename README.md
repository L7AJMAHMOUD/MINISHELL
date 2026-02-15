# 🐚 MINISHELL

> A lightweight, feature-rich shell implementation in C, recreating core functionalities of bash.

![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square)
![Code Quality](https://img.shields.io/badge/Code%20Quality-Good-brightgreen?style=flat-square)
![School](https://img.shields.io/badge/School-42-000000?style=flat-square)

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Built-in Commands](#built-in-commands)
- [Advanced Features](#advanced-features)
- [Code Quality](#code-quality)
- [Authors](#authors)
- [License](#license)

---

## 🎯 Overview

**MINISHELL** is an educational shell implementation that demonstrates deep understanding of systems programming in C. It recreates essential shell functionalities including command execution, piping, redirection, and environment variable management.

This project is ideal for:
- Learning shell internals and process management
- Understanding systems programming concepts
- Exploring Unix/Linux system calls
- Studying command parsing and execution

---

## ✨ Features

### Core Functionality
- ✅ **Command Execution** - Execute system commands with proper argument parsing
- ✅ **Piping** - Chain multiple commands using pipes (`|`)
- ✅ **Input/Output Redirection** - Support for `<`, `>`, `>>` operators
- ✅ **Heredoc** - Here-document syntax support (`<<`)
- ✅ **Environment Variables** - Expand and manage environment variables
- ✅ **Exit Status** - Access exit codes via `$?`
- ✅ **Quote Handling** - Support for both single (`'`) and double (`"`) quotes
- ✅ **Signal Handling** - Proper handling of Ctrl+C and other signals

### Built-in Commands
- 🔨 `cd` - Change directory with PWD/OLDPWD tracking
- 📝 `echo` - Print text to output
- 🚪 `exit` - Exit the shell with exit code
- 🔄 `export` - Manage environment variables
- 🗑️ `unset` - Remove environment variables
- 📊 `env` - Display environment variables
- 🔤 `pwd` - Print working directory

---

## 📦 Requirements

### System Requirements
- Linux/Unix environment
- GCC or Clang compiler
- GNU Make
- Readline library (`libreadline-dev` on Ubuntu/Debian)

### Installation of Dependencies

**Ubuntu/Debian:**
```bash
sudo apt-get install build-essential libreadline-dev
