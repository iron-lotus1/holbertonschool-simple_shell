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
 * get_path - Finds PATH in the environment.
 * @envp: Environment variables.
 *
 * Return: PATH value or NULL.
 */
char *get_path(char **envp)
{
	int i;

	i = 0;

	while (envp[i] != NULL)
	{
		if (envp[i][0] == 'P' &&
		    envp[i][1] == 'A' &&
		    envp[i][2] == 'T' &&
		    envp[i][3] == 'H' &&
		    envp[i][4] == '=')
			return (envp[i] + 5);

		i++;
	}

	return (NULL);
}

/**
 * build_path - Builds a complete path.
 * @directory: Directory from PATH.
 * @command: Command name.
 *
 * Return: Allocated full path.
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
 * find_command - Searches PATH for a command.
 * @command: Command to find.
 * @envp: Environment variables.
 *
 * Return: Full path or NULL.
 */
char *find_command(char *command, char **envp)
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

	path = get_path(envp);

	if (path == NULL || path[0] == '\0')
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
 * @argc: Argument count.
 * @argv: Argument vector.
 * @envp: Environment variables.
 *
 * Return: Exit status.
 */
int main(int argc, char **argv, char **envp)
{
	char *line = NULL;
	char *command_path;
	char *command;
	char *args[64];
	size_t len;
	ssize_t read;
	pid_t pid;
	int status;
	int line_number;
	int last_status;

	(void)argc;
	(void)argv;

	len = 0;
	line_number = 0;
	last_status = 0;

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

		line_number++;

		if (read > 0 && line[read - 1] == '\n')
			line[read - 1] = '\0';

		command = trim_command(line);

		if (command[0] == '\0')
			continue;

		tokenize(command, args);

		/*
		 * Handle the exit built-in.
		 */
		if (strcmp(args[0], "exit") == 0)
		{
			free(line);
			exit(last_status);
		}

		command_path = find_command(args[0], envp);

		/*
		 * Do not fork if command does not exist.
		 */
		if (command_path == NULL)
		{
			fprintf(stderr, "./hsh: %d: %s: not found\n",
				line_number, args[0]);

			last_status = 127;
			continue;
		}

		pid = fork();

		if (pid == -1)
		{
			perror("./hsh");
			free(command_path);
			last_status = 1;
			continue;
		}

		if (pid == 0)
		{
			if (execve(command_path, args, envp) == -1)
			{
				perror("./hsh");
				free(command_path);
				exit(127);
			}
		}
		else
		{
			waitpid(pid, &status, 0);

			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else
				last_status = 1;
		}

		free(command_path);
	}

	free(line);

	return (last_status);
}
