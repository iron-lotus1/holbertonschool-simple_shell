#include "shell.h"

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
 * search_path - Searches PATH directories for a command.
 * @path: PATH environment value.
 * @command: Command to find.
 *
 * Return: Full path to command or NULL.
 */
char *search_path(char *path, char *command)
{
	char *path_copy;
	char *directory;
	char *full_path;

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
 * find_command - Searches PATH for a command.
 * @command: Command to find.
 * @envp: Environment variables.
 *
 * Return: Full path or NULL.
 */
char *find_command(char *command, char **envp)
{
	char *path;

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

	return (search_path(path, command));
}
