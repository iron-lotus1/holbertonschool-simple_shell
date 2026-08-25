#include "shell.h"

/**
 * main - Entry point for the simple shell
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line = NULL;
	char *argv[2];
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	int status;

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

		argv[0] = line;
		argv[1] = NULL;

		pid = fork();

		if (pid == -1)
		{
			perror("./hsh");
			continue;
		}

		if (pid == 0)
		{
			if (execve(line, argv, NULL) == -1)
			{
				perror("./hsh");
				exit(127);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}

	free(line);
	return (0);
}
