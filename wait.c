#include "shell.h"

/**
 * wait_for_process - Waits for a child process.
 * @pid: Process ID of child.
 *
 * Return: Child exit status.
 */
int wait_for_process(pid_t pid)
{
	int status;

	waitpid(pid, &status, 0);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (1);
}
