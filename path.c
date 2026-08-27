#include "shell.h"

/**
 * get_path - Gets the PATH variable from the environment.
 * @env: Environment variables.
 *
 * Return: Pointer to PATH value, or NULL.
 */
char *get_path(char **env)
{
	int i;

	if (env == NULL)
		return (NULL);

	for (i = 0; env[i] != NULL; i++)
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
	}

	return (NULL);
}

/**
 * find_command - Finds the full path of a command.
 * @command: Command name.
 * @env: Environment variables.
 *
 * Return: Full command path, or NULL.
 */
char *find_command(char *command, char **env)
{
	char *path;
	char *path_copy;
	char *directory;
	char *full_path;

	if (command == NULL)
		return (NULL);

	full_path = check_command(command);
	if (full_path != NULL)
		return (full_path);

	path = get_path(env);
	if (path == NULL)
		return (NULL);

	path_copy = malloc(strlen(path) + 1);
	if (path_copy == NULL)
		return (NULL);

	strcpy(path_copy, path);

	directory = strtok(path_copy, ":");

	while (directory != NULL)
	{
		full_path = build_path(directory, command);

		if (full_path != NULL)
		{
			free(path_copy);
			return (full_path);
		}

		directory = strtok(NULL, ":");
	}

	free(path_copy);

	return (NULL);
}
