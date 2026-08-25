#include "shell.h"

/**
 * execute_command - Executes a command
 * @command: Command to execute
 *
 * Return: 0 on success, -1 on failure
 */
int execute_command(char *command)
{
	pid_t pid;
	int status;
	char *argv[2];

	argv[0] = command;
	argv[1] = NULL;

	pid = fork();

	if (pid == -1)
	{
		perror("./hsh");
		return (-1);
	}

	if (pid == 0)
	{
		execve(command, argv, NULL);

		perror("./hsh");
		exit(127);
	}

	waitpid(pid, &status, 0);

	return (0);
}
