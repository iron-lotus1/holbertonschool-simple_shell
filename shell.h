#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

char *trim_spaces(char *str);
int execute_command(char *command);
int handle_builtin(char *command);

#endif /* SHELL_H */
