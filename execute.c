#include "shell.h"

/**
 * execute - Executes an external command.
 * @args: Command arguments.
 * @env: Environment variables.
 * @program: Name of the shell.
 * @line_number: Current command line number.
 *
 * Return: Nothing.
 */
void execute(char **args, char **env,
	     char *program, int line_number)
{
	char *command;

	command = find_command(args[0], env);

	if (command == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			program, line_number, args[0]);
		return;
	}

	run_command(command, args, env, program, line_number);

	free(command);
}

/**
 * run_command - Creates a child and executes a command.
 * @command: Full path to command.
 * @args: Command arguments.
 * @env: Environment variables.
 * @program: Name of the shell.
 * @line_number: Current command line number.
 *
 * Return: Nothing.
 */
void run_command(char *command, char **args, char **env,
		 char *program, int line_number)
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

		fprintf(stderr, "%s: %d: %s: execution failed\n",
			program, line_number, args[0]);

		_exit(127);
	}

	if (waitpid(pid, &status, 0) == -1)
		perror("waitpid");
}
