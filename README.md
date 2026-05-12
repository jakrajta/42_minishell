# 🐚 Minishell

A lightweight Unix shell implementation built in C as part of the 42 School curriculum. This project demonstrates core shell mechanics including process management, system calls, I/O redirection, and signal handling.

## 📋 Overview

Minishell recreates the essential functionality of a POSIX-compliant shell. It's a practical deep dive into how command-line interpreters work under the hood, from parsing user input to executing commands and managing processes.

**Key Achievement:** Successfully handles complex command pipelines, redirections, and environment variable expansion while maintaining the strict 42 coding standards.

## ✨ Features

### Built-in Commands
- **echo** - Print arguments to standard output
- **cd** - Change the working directory
- **pwd** - Print working directory
- **export** - Set environment variables
- **unset** - Remove environment variables
- **env** - Display environment variables
- **exit** - Terminate the shell

### Core Capabilities
- **Process Control** - Forking and executing external commands with `execve`
- **I/O Redirection** - Full support for:
  - `<` (input redirection)
  - `>` (output truncation)
  - `>>` (output append)
  - `<<` (heredoc)
- **Pipelines** - Chain multiple commands with `|` operator
- **Variable Expansion** - Automatic expansion of environment variables and exit status (`$?`)
- **Signal Handling** - Proper POSIX signal management (SIGINT, SIGTERM, etc.) for interactive sessions
- **Quote Handling** - Correct parsing of single and double quotes with escape sequences

## 🛠️ Technical Highlights

### Architecture & Design
- **Tokenizer & Parser** - Robust lexical analysis for complex command lines with nested quotes
- **Process Management** - Efficient pipe creation and file descriptor handling
- **Memory Management** - Careful resource allocation following 42 norms (no memory leaks)

### Key Learning Outcomes
- Deep understanding of process lifecycle and inter-process communication (pipes)
- Safe signal handling using `sigaction()` without global state corruption
- File descriptor manipulation and redirection mechanics
- Shell parsing complexities (quote handling, escape sequences, variable expansion)

## 🚀 Installation & Usage

### Prerequisites
- GCC compiler
- Make build tool
- Unix/Linux environment

### Build & Run

```bash
# Clone the repository
git clone https://github.com/jakrajta/42_minishell.git minishell
cd minishell

# Compile
make

# Run the shell
./minishell
```

### Example Commands

```bash
minishell$ echo "Hello, World!"
Hello, World!

minishell$ pwd
/path/to/minishell

minishell$ ls -la | grep README
-rw-r--r-- ... README.md

minishell$ cat < input.txt > output.txt

minishell$ export MY_VAR=value
minishell$ echo $MY_VAR
value
```

## 📁 Project Structure

```
42_minishell/
├── src/              # Source code
├── includes/         # Header files
├── Makefile         # Build configuration
└── README.md        # This file
```

## 📚 What Makes This Interesting

This project bridges the gap between using a shell and understanding how it works. By building minishell, you gain insight into:
- How your terminal processes and executes commands
- The relationship between processes, file descriptors, and pipes
- How shells manage the environment and built-in commands
- Real-world constraints of C programming (no dynamic memory safety nets)

## 📝 Notes

- Follows 42 School coding standards (Norminette)
- Handles edge cases and signals properly for robust interactive shell usage
- Designed for educational purposes as part of 42 curriculum

---

**Status:** Complete (100/100 Project)
