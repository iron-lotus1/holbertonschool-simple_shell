#include "shell.h"

/**
 * create_process - Creates a child process to execute a command.
 * @args: Command arguments.
 * @envp: Environment variables.
 * @command_path: Full executable path.
 *
 * Return: Command exit status.
 */
int create_process(char **args, char **envp, char *command_path)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == -1)
	{
		perror("./hsh");
		return (1);
	}

	if (pid == 0)
		execute_command(args, envp, command_path);

	status = wait_for_process(pid);

	return (status);
}
