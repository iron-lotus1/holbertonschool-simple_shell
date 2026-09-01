#include "shell.h"

/**
 * trim_command - Removes leading and trailing whitespace.
 * @command: Command to trim.
 *
 * Return: Pointer to the trimmed command.
 */
char *trim_command(char *command)
{
	char *start;
	char *end;

	start = command;

	while (*start == ' ' || *start == '\t')
		start++;

	end = start;

	while (*end != '\0')
		end++;

	if (end != start)
		end--;

	while (end >= start && (*end == ' ' || *end == '\t'))
	{
		*end = '\0';
		end--;
	}

	return (start);
}

/**
 * tokenize - Splits a command into arguments.
 * @command: Command to split.
 * @argv: Array to store arguments.
 *
 * Return: Number of arguments.
 */
int tokenize(char *command, char *argv[])
{
	int count;
	char *start;

	count = 0;

	while (*command != '\0')
	{
		while (*command == ' ' || *command == '\t')
			command++;

		if (*command == '\0')
			break;

		start = command;

		while (*command != '\0' &&
		       *command != ' ' && *command != '\t')
			command++;

		if (*command != '\0')
		{
			*command = '\0';
			command++;
		}

		argv[count] = start;
		count++;

		if (count >= 63)
			break;
	}

	argv[count] = NULL;

	return (count);
}
