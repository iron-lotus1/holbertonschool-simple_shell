#include "shell.h"

/**
 * free_args - Frees an argument array.
 * @args: Argument array.
 *
 * Return: Nothing.
 */
void free_args(char **args)
{
	int i;

	if (args == NULL)
		return;

	i = 0;

	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}

	free(args);
}
