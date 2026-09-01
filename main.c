#include "shell.h"

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
	char *line;
	char *command_path;
	char *args[64];
	size_t len;
	ssize_t read;
	pid_t pid;
	int status;
	int line_number;
	int last_status;

	(void)argc;
	(void)argv;

	line = NULL;
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

				if (line[0] == '\0')
				continue;

				tokenize(line, args);

				if (args[0] == NULL)
				continue;

				command_path = find_command(args[0], envp);

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
				execve(command_path, args, envp);
				perror("./hsh");
				free(command_path);
				free(line);
				exit(127);
			}

			waitpid(pid, &status, 0);

			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else
				last_status = 1;

				free(command_path);
				command_path = NULL;
	}

	free(line);

	return (last_status);
}
