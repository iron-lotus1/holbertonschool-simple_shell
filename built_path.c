#include "shell.h"
#include <stdlib.h>

/**
 * _strlen - Returns the length of a string.
 * @str: String to measure.
 *
 * Return: Length of the string.
 */
int _strlen(char *str)
{
		int length;

		length = 0;

		while (str[length] != '\0')
				length++;

		return (length);
}

/**
 * build_path - Builds the full path of a command.
 * @directory: Directory from PATH.
 * @command: Command to find.
 *
 * Return: Full path, or NULL if memory allocation fails.
 */
char *build_path(char *directory, char *command)
{
		char *full_path;
		int length;
		int i;
		int j;

		if (directory == NULL || command == NULL)
				return (NULL);

		length = _strlen(directory) + _strlen(command) + 2;

		full_path = malloc(sizeof(char) * length);
		if (full_path == NULL)
				return (NULL);

		i = 0;
		while (directory[i] != '\0')
		{
				full_path[i] = directory[i];
				i++;
		}

		full_path[i] = '/';
		i++;

		j = 0;
		while (command[j] != '\0')
		{
				full_path[i] = command[j];
				i++;
				j++;
		}

		full_path[i] = '\0';

		return (full_path);
}
