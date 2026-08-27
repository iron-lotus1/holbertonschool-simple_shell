#include "shell.h"

/**
 * main - Entry point of the simple shell.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line;
	char **args;
	int num_tokens;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf(":) ");

		line = user_input();

		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		args = token(line, &num_tokens);

		if (args != NULL && args[0] != NULL)
			process_command(args, environ);

		free_args(args);
		free(line);
	}

	return (0);
}
