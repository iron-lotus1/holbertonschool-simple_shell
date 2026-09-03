# Simple Shell

## Description

`simple_shell` is a simple UNIX command-line interpreter written in C.

The shell displays a prompt, waits for the user to type a command, executes the command, and displays the prompt again after the command has been executed.

This project is part of the Holberton School curriculum and introduces:

- UNIX processes
- Process creation
- System calls
- Command execution
- Error handling
- Standard input and output

## Usage

Start the shell with:

./hsh

The shell displays a prompt:

$ 

Enter a command followed by a new line:

$ ls
$ pwd
$ whoami

The prompt is displayed again after each command has been executed.

To exit the shell, press:

Ctrl+D

## Compilation

Compile the shell with:

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

## Examples

Interactive mode:

$ ./hsh
$ ls
AUTHORS  README.md  main.c  shell.h
$ pwd
/home/user/simple_shell
$ whoami
user
$

If an executable cannot be found, the shell prints an error message and displays the prompt again:

$ ./hsh
$ nonexistent
./hsh: 1: nonexistent: not found
$

## Features

The shell:

- Displays a prompt.
- Reads commands from standard input.
- Executes commands.
- Displays the prompt again after each command.
- Handles errors.
- Handles the end-of-file condition (Ctrl+D).

## Limitations

This shell is intentionally simple.

It does not:

- Use the PATH environment variable.
- Implement built-in commands.
- Handle commands with arguments.
- Handle semicolons (;).
- Handle pipes (|).
- Handle redirections.
- Handle special characters such as:
  - "
  - '
  - `
  - \
  - *
  - &
  - #
- Support cursor movement.

Command lines contain only one word.

## Files

|       File                                   |      Description                           |
|       ----                                   |      -----------                           |
| [main.c](./main.c)                           | Main entry point of the shell              |
| [prompt.c](./prompt.c)                       | Reads the command and shows prompt         |
| [token.c](./token.c)                         | Trims and splits command                   |
| [process.c](./process.c)                     | Decides what to do with the command        |
| [builtins.c](./builtins.c)                   | Handles exit and env                       |
| [env.c](./env.c)                             | Prints environment variables               |
| [path.c](./path.c)                           | Finds the command in the PATH              |
| [execute.c](./execute.c)                     | Executes the command with execve           |
| [fork.c](./fork.c)                           | Creates a child process                    |
| [wait.c](./wait.c)                           | Waits for the child process                |
| [shell.h](./shell.h)                         | Header file containing function prototypes |
| [README.md](./README.md)                     | Project documentation                      |
| [man_1_simple_shell](./man_1_simple_shell)   | Manual page for the shell                  |
| [AUTHORS](./AUTHORS)                         | List of project contributors               |

## Man Page

The manual page is located in:

man_1_simple_shell

View it with:

man ./man_1_simple_shell

## Authors

See the `AUTHORS` file for the list of contributors.
