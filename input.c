#include "shell.h"

/**
 * user_input - Reads a command line from the user.
 *
 * Return: Input line, or NULL on EOF/error.
 */
char *user_input(void)
{
	char *line = NULL;
	size_t n = 0;

	if (getline(&line, &n, stdin) == -1)
	{
		free(line);
		return (NULL);
	}

	return (line);
}
