#include "shell.h"

/**
 * read_command - Reads a command from standard input.
 *
 * Return: Allocated command line, or NULL on EOF/error.
 */
char *read_command(void)
{
	char *line;
	size_t len;
	ssize_t read;

	line = NULL;
	len = 0;

	if (isatty(STDIN_FILENO))
		printf("$ ");

	read = getline(&line, &len, stdin);

	if (read == -1)
	{
		if (isatty(STDIN_FILENO))
			printf("\n");

		free(line);
		return (NULL);
	}

	if (read > 0 && line[read - 1] == '\n')
		line[read - 1] = '\0';

	return (line);
}
