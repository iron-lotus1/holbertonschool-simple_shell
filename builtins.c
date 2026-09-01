#include "shell.h"

/**
 * handle_builtin - Handles shell built-in commands.
 * @args: Command arguments.
 * @envp: Environment variables.
 * @status: Previous exit status.
 *
 * Return: New status, or -1 if command is not a built-in.
 */
int handle_builtin(char **args, char **envp, int status)
{
	if (args == NULL || args[0] == NULL)
		return (-1);

	if (strcmp(args[0], "exit") == 0)
	{
		exit(status);
	}

	if (strcmp(args[0], "env") == 0)
	{
		print_environment(envp);
		return (0);
	}

	return (-1);
}
