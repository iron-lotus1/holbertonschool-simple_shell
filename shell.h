#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void print_prompt(void);
void execute_command(char *command);
char *trim_command(char *command);
int tokenize(char *command, char *argv[]);

#endif
