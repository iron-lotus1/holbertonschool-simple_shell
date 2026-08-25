#include "shell.h"

/**
 * main - Entry point for the simple shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");

		if (getline(&line, &len, stdin) == -1)
		{
			free(line);
			return (0);
		}

		line[strcspn(line, "\n")] = '\0';

		if (line[0] == '\0')
			continue;

		execute_command(line);
	}

	free(line);
	return (0);
}
