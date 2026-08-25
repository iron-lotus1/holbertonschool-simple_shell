#include "shell.h"

/**
 * execute_command - Executes a command
 * @command: Command to execute
 * @program_name: Name of the shell program
 *
 * Return: Nothing
 */
void execute_command(char *command, char *program_name)
{
	pid_t pid;
	int status;
	char *args[2];

	args[0] = command;
	args[1] = NULL;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		execve(command, args, NULL);

		print_error(program_name, command);
		exit(127);
	}

	waitpid(pid, &status, 0);
}
