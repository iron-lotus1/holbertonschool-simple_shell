#include "shell.h"

/**
<<<<<<< HEAD
 * main - Entry point of the simple shell.
 * @ac: Number of command-line arguments.
 * @av: Array of command-line arguments.
 * @env: Array of environment variables.
 *
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
	char *line;
	char **args;
	int num_tokens;

	(void)ac;
	(void)av;

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
		if (args != NULL)
			process_command(args, env);

		free_args(args);
		free(line);
	}

	return (0);
}