#include "shell.h"

/**
 * build_path - Builds a complete command path.
 * @directory: Directory from PATH.
 * @command: Command name.
 *
 * Return: Full executable path, or NULL.
 */
char *build_path(char *directory, char *command)
{
	char *full_path;
	size_t length;

	length = strlen(directory) + strlen(command) + 2;

	full_path = malloc(length);
	if (full_path == NULL)
		return (NULL);

	strcpy(full_path, directory);
	strcat(full_path, "/");
	strcat(full_path, command);

	if (access(full_path, X_OK) == 0)
		return (full_path);

	free(full_path);

	return (NULL);
}

/**
 * check_command - Checks a command containing '/'.
 * @command: Command name or path.
 *
 * Return: Command path, or NULL.
 */
char *check_command(char *command)
{
	char *full_path;

	if (strchr(command, '/') == NULL)
		return (NULL);

	if (access(command, F_OK) != 0)
		return (NULL);

	full_path = malloc(strlen(command) + 1);
	if (full_path == NULL)
		return (NULL);

	strcpy(full_path, command);

	return (full_path);
}

/**
 * search_path - Searches directories in PATH for a command.
 * @path: PATH string.
 * @command: Command name.
 *
 * Return: Full command path, or NULL.
 */
char *search_path(char *path, char *command)
{
	char *directory;
	char *full_path;

	directory = strtok(path, ":");

	while (directory != NULL)
	{
		full_path = build_path(directory, command);

		if (full_path != NULL)
			return (full_path);

		directory = strtok(NULL, ":");
	}

	return (NULL);
}
