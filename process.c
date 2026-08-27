#include "shell.h"

/**
 * process_command - Processes a command.
 * @args: Command arguments.
 * @env: Environment variables.
 * @program: Name of the shell.
 * @line_number: Current command line number.
 *
 * Return: Nothing.
 */
void process_command(char **args, char **env,
		     char *program, int line_number)
{
	if (is_builtin(args))
	{
		handle_builtin(args, env);
	}
	else
	{
		execute(args, env, program, line_number);
	}
}
