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
 * tokenize - Splits a command line into arguments.
 * @command: Command line.
 * @argv: Array to store the arguments.
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
		       *command != ' ' &&
		       *command != '\t')
		{
			command++;
		}

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

/**
 * main - Entry point for the simple shell.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line = NULL;
	char *command;
	char *argv[64];
	size_t len;
	ssize_t read;
	pid_t pid;
	int status;

	len = 0;

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

		tokenize(command, argv);

		pid = fork();

		if (pid == -1)
		{
			perror("./hsh");
			continue;
		}

		if (pid == 0)
		{
			if (execve(argv[0], argv, NULL) == -1)
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
