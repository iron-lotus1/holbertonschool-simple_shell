#include "shell.h"

/**
 * print_environment - Prints the current environment.
 * @envp: Environment variables.
 */
void print_environment(char **envp)
{
	int i;

	i = 0;

	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
}
