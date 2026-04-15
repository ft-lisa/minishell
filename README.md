# Minishell

42 Common Core project – Unix shell implementation in C.

---

## Overview

Minishell is a simplified Unix shell written in C, designed to replicate core behaviors of a real shell (like bash).

It supports command execution, pipelines, redirections, environment variables, and signal handling.

The goal of the project is to deeply understand how a shell works internally, including process creation, file descriptor management, and parsing complex command inputs.

---

## Features

### Command execution
- Execution of built-in and external commands
- Path resolution using `PATH` environment variable
- Proper error handling for invalid commands

### Pipes and redirections
- Support for pipes (`|`)
- Input redirection (`<`)
- Output redirection (`>`, `>>`)
- Multiple chained commands

### Built-in commands
- `echo`
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

### Environment handling
- Environment variable expansion (`$VAR`)
- Dynamic update of environment variables

### Signal handling
- Proper handling of `Ctrl+C`, `Ctrl+\`, `Ctrl+D`
- Interactive shell behavior similar to bash

### Parser
- Robust command parsing
- Quote handling (`'` and `"`)
- Edge case management (empty commands, malformed input)

---

## Technical Stack

- Language: C
- System calls: `fork`, `execve`, `pipe`, `dup2`, `wait`
- Standard library + POSIX functions
- Memory management: manual allocation/free

---

## Challenges

- Managing multiple processes with correct synchronization
- Handling complex parsing cases (quotes, escapes, nested commands)
- Ensuring correct file descriptor management (avoid leaks)
- Reproducing bash-like behavior consistently

---

## Compilation

```bash
make all
```