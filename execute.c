#include "shell.h"

/**
 * execute - Executes an external command.
 * @args: Command and arguments.
 * @env: Environment variables.
 */
void execute(char **args, char **env)
{
	char *command;

	command = find_command(args[0], env);
	if (command == NULL)
	{
		fprintf(stderr, "%s: not found\n", args[0]);
		return;
	}

	run_command(command, args, env);
	free(command);
}

/**
 * get_command - Finds the command to execute.
 * @command: Command name.
 * @env: Environment variables.
 *
 * Return: Command path, or NULL.
 */
char *get_command(char *command, char **env)
{
	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (command);

		return (NULL);
	}

	return (find_command(command, env));
}

/**
 * run_command - Creates a process and executes a command.
 * @command: Full path to the command.
 * @args: Command arguments.
 * @env: Environment variables.
 */
void run_command(char *command, char **args, char **env)
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
		execve(command, args, env);
		perror(args[0]);
		_exit(127);
	}

	if (waitpid(pid, &status, 0) == -1)
		perror("waitpid");
}
