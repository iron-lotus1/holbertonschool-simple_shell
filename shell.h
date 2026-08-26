#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

char *trim_command(char *command);
int tokenize(char *command, char *argv[]);
char *get_path(char **envp);
char *build_path(char *directory, char *command);
char *find_command(char *command, char **envp);

#endif
