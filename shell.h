#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Global environment */
extern char **environ;

/* input.c */
char *user_input(void);

/* token.c */
int count_tokens(char *line);
int fill_args(char *line, char **args);
char **token(char *line, int *num_tokens);

/* process.c */
void process_command(char **args, char **env);

/* execute.c */
void execute(char **args, char **env);
void run_command(char *command, char **args, char **env);

/* free_args.c */
void free_args(char **args);

/* path.c */
char *get_path(char **env);
char *find_command(char *command, char **env);

/* builtins.c */
int is_builtin(char **args);
void builtin_exit(char **args);
void builtin_env(char **env);

#endif
