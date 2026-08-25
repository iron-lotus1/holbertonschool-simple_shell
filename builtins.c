#include "shell.h"

/**
 * handle_builtin - Handles built-in commands
 * @command: Command entered by the user
 *
 * Return: 1 if built-in, 0 otherwise
 */
int handle_builtin(char *command)
{
	if (strcmp(command, "exit") == 0)
	{
		exit(0);
	}

	return (0);
}
