# Simple Shell

## Description

`simple_shell` is a simple UNIX command-line interpreter written in C.

The shell displays a prompt, waits for the user to type a command, executes the command, and displays the prompt again after the command has been executed.

This project is part of the Holberton School curriculum and is designed to introduce the concepts of:

* UNIX processes
* Process creation
* System calls
* Command execution
* Error handling
* Standard input and output
* Environment variables

## Usage

Start the shell by running:

```bash
./hsh
```

The shell displays a prompt and waits for a command:

```text
$ 
```

Enter a command followed by Enter:

```text
$ ls
$ pwd
$ whoami
```

The prompt is displayed again after each command has been executed.

To exit the shell, press:

```text
Ctrl+D
```

## Compilation

Compile the shell using:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Examples

### Interactive mode

```text
$ ./hsh
$ ls
AUTHORS  README.md  main.c  shell.h
$ pwd
/home/user/simple_shell
$ whoami
user
$ 
```

### Command not found

If an executable cannot be found, the shell displays an error message and displays the prompt again.

```text
$ ./hsh
$ nonexistent
./hsh: 1: nonexistent: not found
$ 
```

## Supported Features

The shell:

* Displays a prompt.
* Reads commands from standard input.
* Executes commands.
* Displays the prompt again after each command.
* Handles errors.
* Handles the end-of-file condition (`Ctrl+D`).

## Limitations

This shell is intentionally simple.

It does not:

* Use the `PATH` environment variable to locate commands.
* Implement built-in commands.
* Handle command arguments.
* Handle semicolons (`;`).
* Handle pipes (`|`).
* Handle redirections (`>`, `<`, `>>`, etc.).
* Handle special characters such as `"`, `'`, `` ` ``, `\`, `*`, `&`, and `#`.
* Support cursor movement.

Command lines contain only one word.

## Files

| File                 | Description                                  |
| -------------------- | -------------------------------------------- |
| `main.c`             | Contains the main entry point of the shell   |
| `shell.h`            | Contains function prototypes and definitions |
| `README.md`          | Project documentation                        |
| `man_1_simple_shell` | Manual page for the shell                    |
| `AUTHORS`            | Lists the contributors to the repository     |

## Man Page

The manual page for the shell is located in:

```text
man_1_simple_shell
```

It can be viewed with:

```bash
man ./man_1_simple_shell
```

## Authors

See the `AUTHORS` file for the list of contributors.

