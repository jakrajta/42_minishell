# MINISHELL

DESCRIPTION

Minishell is a project designed to recreate the core mechanics of a Unix shell. 
It serves as a deep dive into process management, system calls, and the lifecycle of command execution in C.
The primary objective was to build a functional command-line interpreter that supports piping, redirections, 
environment variables, and signal handling, while adhering to the strict 42 coding standards and architectural constraints.



FEATURES

Built-ins: echo, cd, pwd, export, unset, env, exit.

Process Control: Forking, execution with execve, and handling wait-states.

I/O Redirection: Supports < (input), > (truncate), >> (append), and << (heredoc).

Pipelines: Efficient handling of | to chain multiple commands.

Environment: Variable expansion, exit status reporting.

Signals: Correct POSIX signal management for interactive terminal sessions.


TECHNICAL HIGHLIGHTS & LEARNINGS

Process Management: Gained practical experience in isolating processes and managing pipes to link standard output of one command to the standard input of another.

Signal Handling: Learned how to safely manage signals using sigaction without corrupting global state.

Parsing: Implemented a robust tokenizer and parser to handle complex command lines with nested quotes and redirections.



INSTALATION & USAGE

Clone the repository:

```Bash
git clone https://github.com/jakrajta/42_minishell.git minishell
cd minishell
```

Compile:

```Bash
make
```

Run:

```Bash
./minishell
```
