#include "shell.h"

/**
 * is_builtin - Checks whether a command is built-in.
 * @args: Command arguments.
 *
 * Return: 1 if built-in, 0 otherwise.
 */
int is_builtin(char **args)
{
	if (strcmp(args[0], "exit") == 0)
		return (1);

	if (strcmp(args[0], "env") == 0)
		return (1);

	return (0);
}

/**
 * handle_builtin - Executes a built-in command.
 * @args: Command arguments.
 * @env: Environment variables.
 *
 * Return: Nothing.
 */
void handle_builtin(char **args, char **env)
{
	if (strcmp(args[0], "exit") == 0)
		builtin_exit(args);
	else if (strcmp(args[0], "env") == 0)
		builtin_env(env);
}

/**
 * builtin_exit - Exits the shell.
 * @args: Command arguments.
 *
 * Return: Nothing.
 */
void builtin_exit(char **args)
{
	(void)args;
	exit(0);
}

/**
 * builtin_env - Prints the environment.
 * @env: Environment variables.
 *
 * Return: Nothing.
 */
void builtin_env(char **env)
{
	int i;

	for (i = 0; env[i] != NULL; i++)
		printf("%s\n", env[i]);
}
