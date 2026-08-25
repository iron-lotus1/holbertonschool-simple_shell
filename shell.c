#include "shell.h"

/**
 * trim_spaces - Removes leading and trailing spaces
 * @str: String to trim
 *
 * Return: Pointer to trimmed string
 */
char *trim_spaces(char *str)
{
	char *end;

	while (*str == ' ' || *str == '\t')
		str++;

	if (*str == '\0')
		return (str);

	end = str + strlen(str) - 1;

	while (end > str && (*end == ' ' || *end == '\t'))
		end--;

	*(end + 1) = '\0';

	return (str);
}

/**
 * main - Entry point for the simple shell
 *
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL;
	char *command;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");

		nread = getline(&line, &len, stdin);

		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		command = trim_spaces(line);

		if (*command == '\0')
			continue;

		if (handle_builtin(command))
			continue;

		execute_command(command);
	}

	free(line);
	return (0);
}
