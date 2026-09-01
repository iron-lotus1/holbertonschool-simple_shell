#include "shell.h"

/**
 * execute_command - Executes an external command.
 * @args: Command arguments.
 * @envp: Environment variables.
 * @command_path: Full path to executable.
 *
 * Return: Command exit status.
 */
int execute_command(char **args, char **envp, char *command_path)
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
	{
		if (execve(command_path, args, envp) == -1)
		{
			perror("./hsh");
			_exit(127);
		}
	}

	waitpid(pid, &status, 0);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (1);
}
