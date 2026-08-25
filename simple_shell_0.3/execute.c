#include "shell.h"

/**
 * execute_command - Executes a command
 * @args: Array containing command and arguments
 * @program_name: Name of the shell
 *
 * Return: Nothing
 */
void execute_command(char **args, char *program_name)
{
	pid_t pid;
	int status;
	char *command_path;

	command_path = find_command(args[0]);

	if (command_path == NULL)
	{
		print_error(program_name, args[0]);
		return;
	}

	args[0] = command_path;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		free(command_path);
		return;
	}

	if (pid == 0)
	{
		execve(command_path, args, NULL);

		perror("execve");
		free(command_path);
		exit(127);
	}

	waitpid(pid, &status, 0);

	free(command_path);
}
