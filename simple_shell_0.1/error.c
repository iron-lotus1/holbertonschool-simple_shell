#include "shell.h"

/**
 * print_error - Prints an error message
 * @program_name: Name of the shell program
 * @command: Command that failed
 *
 * Return: Nothing
 */
void print_error(char *program_name, char *command)
{
	fprintf(stderr, "%s: 1: %s: not found\n", program_name, command);
}
