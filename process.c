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
	if (args == NULL || args[0] == NULL)
		return;

	if (is_builtin(args))
		handle_builtin(args, env);
	else
		execute(args, env);
}
