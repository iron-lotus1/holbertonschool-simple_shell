#include "shell.h"

/**
 * count_tokens - Counts command arguments.
 * @line: Command line.
 *
 * Return: Number of tokens.
 */
int count_tokens(char *line)
{
	char *copy;
	char *word;
	int count = 0;

	copy = malloc(strlen(line) + 1);
	if (copy == NULL)
		return (0);

	strcpy(copy, line);
	word = strtok(copy, " \n");

	while (word != NULL)
	{
		count++;
		word = strtok(NULL, " \n");
	}

	free(copy);
	return (count);
}

/**
 * fill_args - Copies tokens into an argument array.
 * @line: Command line.
 * @args: Argument array.
 *
 * Return: 0 on success, -1 on failure.
 */
int fill_args(char *line, char **args)
{
	char *copy;
	char *word;
	int i = 0;

	copy = malloc(strlen(line) + 1);
	if (copy == NULL)
		return (-1);

	strcpy(copy, line);
	word = strtok(copy, " \n");

	while (word != NULL)
	{
		args[i] = malloc(strlen(word) + 1);
		if (args[i] == NULL)
		{
			free(copy);
			free_args(args);
			return (-1);
		}

		strcpy(args[i], word);
		i++;
		word = strtok(NULL, " \n");
	}

	args[i] = NULL;
	free(copy);

	return (0);
}

/**
 * token - Splits a command line into arguments.
 * @line: Command line.
 * @num_tokens: Number of arguments.
 *
 * Return: Array of arguments, or NULL.
 */
char **token(char *line, int *num_tokens)
{
	char **args;
	int count;

	count = count_tokens(line);
	*num_tokens = count + 1;

	args = malloc(sizeof(char *) * (*num_tokens));
	if (args == NULL)
		return (NULL);

	if (fill_args(line, args) == -1)
	{
		free(args);
		return (NULL);
	}

	return (args);
}
