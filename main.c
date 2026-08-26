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
		       *command != ' ' &&
		       *command != '\t')
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

/**
 * get_path - Gets the PATH environment variable.
 *
 * Return: Pointer to PATH or NULL.
 */
char *get_path(void)
{
	char *path;

	path = getenv("PATH");

	return (path);
}

/**
 * build_path - Creates a possible path for a command.
 * @directory: Directory from PATH.
 * @command: Command name.
 *
 * Return: Allocated full path or NULL.
 */
char *build_path(char *directory, char *command)
{
	char *full_path;
	int length;

	length = strlen(directory) + strlen(command) + 2;

	full_path = malloc(length);

	if (full_path == NULL)
		return (NULL);

	strcpy(full_path, directory);
	strcat(full_path, "/");
	strcat(full_path, command);

	return (full_path);
}

/**
 * find_command - Searches PATH for an executable.
 * @command: Command to find.
 *
 * Return: Full path to executable or NULL.
 */
char *find_command(char *command)
{
	char *path;
	char *path_copy;
	char *directory;
	char *full_path;

	if (command == NULL)
		return (NULL);

	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));

		return (NULL);
	}

	path = get_path();

	if (path == NULL)
		return (NULL);

	path_copy = strdup(path);

	if (path_copy == NULL)
		return (NULL);

	directory = strtok(path_copy, ":");

	while (directory != NULL)
	{
		full_path = build_path(directory, command);

		if (full_path != NULL)
		{
			if (access(full_path, X_OK) == 0)
			{
				free(path_copy);
				return (full_path);
			}

			free(full_path);
		}

		directory = strtok(NULL, ":");
	}

	free(path_copy);

	return (NULL);
}

/**
 * main - Entry point for the simple shell.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line = NULL;
	char *command_path;
	char *argv[64];
	char *command;
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

		command_path = find_command(argv[0]);

		if (command_path == NULL)
		{
			fprintf(stderr, "./hsh: %s: not found\n", argv[0]);
			continue;
		}

		pid = fork();

		if (pid == -1)
		{
			perror("./hsh");
			free(command_path);
			continue;
		}

		if (pid == 0)
		{
			if (execve(command_path, argv, NULL) == -1)
			{
				perror("./hsh");
				free(command_path);
				exit(127);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
		}

		free(command_path);
	}

	free(line);

	return (0);
}
