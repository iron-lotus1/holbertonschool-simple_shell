#include "shell.h"

/**
 * find_command - Finds a command in PATH
 * @command: Command to find
 *
 * Return: Full path to command, or NULL if not found
 */
char *find_command(char *command)
{
	char *path;
	char *path_copy;
	char *directory;
	char *full_path;
	size_t length;

	if (command == NULL)
		return (NULL);

	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));

		return (NULL);
	}

	path = getenv("PATH");

	if (path == NULL)
		return (NULL);

	path_copy = strdup(path);

	if (path_copy == NULL)
		return (NULL);

	directory = strtok(path_copy, ":");

	while (directory != NULL)
	{
		length = strlen(directory) + strlen(command) + 2;

		full_path = malloc(length);

		if (full_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}

		sprintf(full_path, "%s/%s", directory, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);

		directory = strtok(NULL, ":");
	}

	free(path_copy);

	return (NULL);
}
