#include "shell.h"

/**
 * free_args - Frees an argument array.
 * @args: Array of arguments.
 *
 * Return: Nothing.
 */
void free_args(char **args)
{
	int i;

	if (args == NULL)
		return;

	for (i = 0; args[i] != NULL; i++)
		free(args[i]);

	free(args);
}
