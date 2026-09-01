#include "shell.h"

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

	full_path = search_path(path_copy, command);

	free(path_copy);

	return (full_path);
}

/**
 * This is a test code
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
