#include "shell.h"

/**
 * execute_command - Executes a command with arguments
 * @args: Array containing command and arguments
 * @program_name: Name of the shell
 *
 * Return: Nothing
 */
void execute_command(char **args, char *program_name)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		execve(args[0], args, NULL);

		print_error(program_name, args[0]);
		exit(127);
	}

	waitpid(pid, &status, 0);
}
