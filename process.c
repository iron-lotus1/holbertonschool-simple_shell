#include "shell.h"

/**
 * process_command - Processes a command.
 * @args: Command arguments.
 * @envp: Environment variables.
 * @status: Previous exit status.
 *
 * Return: New exit status.
 */
int process_command(char **args, char **envp, int status, int line_number, char *line)
{
	char *command_path;
	int builtin_status;

	if (strcmp(args[0], "exit") == 0)
	{
		free(line);
		exit(status);
	}

	builtin_status = handle_builtin(args, envp, status);

	if (builtin_status != -1)
		return (builtin_status);

	command_path = find_command(args[0], envp);

	if (command_path == NULL)
	{
		fprintf(stderr, "./hsh: %d: %s: not found\n",
				line_number, args[0]);
		return (127);
	}

	status = execute_command(args, envp, command_path);

	free(command_path);

	return (status);
}
