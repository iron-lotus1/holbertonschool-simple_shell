# holbertonschool-simple_shell

# Simple Shell

## Description

This project is a simple UNIX command-line interpreter written in C.

The shell displays a prompt, waits for the user to enter a command, executes the command, and displays the prompt again.

The project is part of the Holberton School curriculum and focuses on processes, system calls, environment variables, and command execution.

## Compilation

The shell can be compiled with:

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

## Usage

Run the shell with:

./hsh

The shell will display a prompt:

$ 

You can then enter commands such as:

$ ls
$ pwd
$ whoami

To exit the shell, press Ctrl+D.

## Features

The shell supports:

- Interactive mode
- Non-interactive mode
- Command execution
- Searching for commands using PATH
- Error handling
- End-of-file handling

## Examples

Interactive mode:

$ ./hsh
$ ls
$ pwd
$ whoami

Non-interactive mode:

$ echo "ls" | ./hsh

## Man Page

A manual page for the shell is available in:

man_1_simple_shell

It can be viewed with:

man ./man_1_simple_shell

## Authors

See the AUTHORS file for the list of contributors.
