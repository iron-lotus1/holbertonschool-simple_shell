#include "shell.h"

/**
 * trim_command - Removes leading and trailing spaces from a command.
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

	end--;

	while (end >= start && (*end == ' ' || *end == '\t'))
	{
		*end = '\0';
		end--;
	}

	return (start);
}

/**
 * main - Entry point for the simple shell.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line = NULL;
	char *command;
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

		command = trim_command(line);

		if (command[0] == '\0')
			continue;

		argv[0] = command;
		argv[1] = NULL;

		pid = fork();

		if (pid == -1)
		{
			perror("./hsh");
			continue;
		}

		if (pid == 0)
		{
			if (execve(command, argv, NULL) == -1)
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
