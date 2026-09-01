#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


/* input.c */
char *read_command(void);

/* token.c */
int tokenize(char *command, char *argv[]);
char *trim_command(char *command);

/* builtins.c */
int handle_builtin(char **args, char **envp, int status);

/* process.c */
int process_command(char **args, char **envp, int status);

/* env.c */
void print_environment(char **envp);

/* execute.c */
int execute_command(char **args, char **envp, char *command_path);

/* path.c */
char *get_path(char **envp);
char *build_path(char *directory, char *command);
char *search_path(char *path, char *command);
char *find_command(char *command, char **envp);

#endif

