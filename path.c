#include "shell.h"

/**
 * get_path - Finds PATH in the environment.
 * @env: Environment variables.
 *
 * Return: PATH value, or NULL.
 */
char *get_path(char **env)
{
	int i;

	for (i = 0; env[i] != NULL; i++)
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
	}

	return (NULL);
}

/**
 * build_path - Creates a full command path.
 * @directory: PATH directory.
 * @command: Command name.
 *
 * Return: Full path, or NULL.
 */
char *build_path(char *directory, char *command)
{
	char *full_path;

	full_path = malloc(strlen(directory) + strlen(command) + 2);
	if (full_path == NULL)
		return (NULL);

	strcpy(full_path, directory);
	strcat(full_path, "/");
	strcat(full_path, command);

	return (full_path);
}

/**
 * search_path - Searches PATH for a command.
 * @path: PATH value.
 * @command: Command name.
 *
 * Return: Full path, or NULL.
 */
char *search_path(char *path, char *command)
{
	char *copy;
	char *directory;
	char *full_path;

	copy = malloc(strlen(path) + 1);
	if (copy == NULL)
		return (NULL);

	strcpy(copy, path);
	directory = strtok(copy, ":");

	while (directory != NULL)
	{
		full_path = build_path(directory, command);

		if (full_path != NULL && access(full_path, X_OK) == 0)
		{
			free(copy);
			return (full_path);
		}

		free(full_path);
		directory = strtok(NULL, ":");
	}

	free(copy);
	return (NULL);
}

/**
 * find_command - Finds a command in PATH.
 * @command: Command name.
 * @env: Environment variables.
 *
 * Return: Full path, or NULL.
 */
char *find_command(char *command, char **env)
{
	char *path;

	path = get_path(env);

	if (path == NULL)
		return (NULL);

	return (search_path(path, command));
}
