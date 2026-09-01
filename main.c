#include "shell.h"

/**
 * main - Entry point for the simple shell.
 * @argc: Argument count.
 * @argv: Argument vector.
 * @envp: Environment variables.
 *
 * Return: Exit status.
 */
int main(int argc, char **argv, char **envp)
{
	char *line;
	char *command;
	char *args[64];
	int status;

	(void)argc;
	(void)argv;

	line = NULL;
	status = 0;

	while (1)
	{
		line = read_command();

		if (line == NULL)
			break;

		command = trim_command(line);

		if (command[0] == '\0')
		{
			free(line);
			line = NULL;
			continue;
		}

		tokenize(command, args);
		status = process_command(args, envp, status);

		free(line);
		line = NULL;
	}

	return (status);
}
