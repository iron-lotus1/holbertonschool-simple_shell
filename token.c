#include "shell.h"

/**
 * count_tokens - Counts the number of tokens in a command line.
 * @line: Command line.
 *
 * Return: Number of tokens.
 */
int count_tokens(char *line)
{
	char *copy;
	char *word;
	int count = 0;

	if (line == NULL)
		return (0);

	copy = malloc(strlen(line) + 1);
	if (copy == NULL)
		return (0);

	strcpy(copy, line);

	word = strtok(copy, " \t\n");
	while (word != NULL)
	{
		count++;
		word = strtok(NULL, " \t\n");
	}

	free(copy);
	return (count);
}

/**
 * fill_args - Copies tokens into an argument array.
 * @line: Command line.
 * @args: Argument array (already allocated).
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

	word = strtok(copy, " \t\n");
	while (word != NULL)
	{
		args[i] = malloc(strlen(word) + 1);
		if (args[i] == NULL)
		{
			/* Free only the tokens we successfully allocated */
			while (i > 0)
			{
				i--;
				free(args[i]);
			}
			free(copy);
			return (-1);
		}

		strcpy(args[i], word);
		i++;
		word = strtok(NULL, " \t\n");
	}

	args[i] = NULL; /* Always NULL-terminate */
	free(copy);
	return (0);
}

/**
 * token - Splits a command line into arguments.
 * @line: Command line.
 * @num_tokens: Pointer to store number of arguments (including NULL).
 *
 * Return: Array of arguments, or NULL on failure.
 */
char **token(char *line, int *num_tokens)
{
	char **args;
	int count;

	if (line == NULL || num_tokens == NULL)
		return (NULL);

	count = count_tokens(line);
	*num_tokens = count + 1;

	args = malloc(sizeof(char *) * (*num_tokens));
	if (args == NULL)
		return (NULL);

	args[0] = NULL;

	if (fill_args(line, args) == -1)
	{
		free(args);
		return (NULL);
	}

	return (args);
}
