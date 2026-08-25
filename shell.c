#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	char *argv[2];

	while (1)
	{
		printf("#cisfun$ ");
		fflush(stdout);

		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			free(line);
			return (0);
		}

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		if (line[0] == '\0')
			continue;

		argv[0] = line;
		argv[1] = NULL;

		pid = fork();

		if (pid == -1)
		{
			perror("./shell");
			continue;
		}

		if (pid == 0)
		{
			execve(argv[0], argv, NULL);
			perror("./shell");
			exit(127);
		}

		waitpid(pid, NULL, 0);
	}

	free(line);
	return (0);
}
