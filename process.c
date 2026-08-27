#include "shell.h"

/**
 * process_command - Processes a command.
 * @args: Command arguments.
 * @env: Environment variables.
 *
 * Return: Nothing.
 */
void process_command(char **args, char **env)
{
	if (is_builtin(args))
	{
		if (strcmp(args[0], "exit") == 0)
			builtin_exit(args);
		else if (strcmp(args[0], "env") == 0)
			builtin_env(env);
	}
	else
	{
		execute(args, env);
	}
}
