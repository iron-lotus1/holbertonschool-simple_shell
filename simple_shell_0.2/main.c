#include "shell.h"

/**
 * main - Entry point for the simple shell
 * @argc: Number of arguments
 * @argv: Array of arguments
 *
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	char *token;
	char *args[MAX_ARGS];
	size_t len = 0;
	ssize_t read;
	int count;

	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");

		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		if (read > 0 && line[read - 1] == '\n')
			line[read - 1] = '\0';

		if (line[0] == '\0')
			continue;

		count = 0;
		token = strtok(line, " ");

		while (token != NULL && count < MAX_ARGS - 1)
		{
			args[count] = token;
			count++;
			token = strtok(NULL, " ");
		}

		args[count] = NULL;

		execute_command(args, argv[0]);
	}

	free(line);

	return (0);
}
