#include "shell.h"

/**
 * main - Entry point of the simple shell.
 * @ac: Number of arguments.
 * @av: Array of arguments.
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
	char *line;
	char **args;
	int num_tokens = 0;
	int line_number = 0;

	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("$ ");
			fflush(stdout);
		}

		line = user_input();

		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		line_number++;

		args = token(line, &num_tokens);

		if (args != NULL && args[0] != NULL)
			process_command(args, environ, av[0], line_number);

		free_args(args);
		free(line);
	}

	return (0);
}
