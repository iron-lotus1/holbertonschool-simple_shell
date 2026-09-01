#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

/* input.c */
char *user_input(void);

/* token.c */
int count_tokens(char *line);
int fill_args(char *line, char **args);
char **token(char *line, int *num_tokens);

/* process.c */
void process_command(char **args, char **env,
char *program, int line_number);

/* builtins.c */
int is_builtin(char **args);
void handle_builtin(char **args, char **env);
void builtin_exit(char **args);
void builtin_env(char **env);

/* env.c */
void print_environment(char **envp);

/* execute.c */
void execute(char **args, char **env,
	     char *program, int line_number);
void run_command(char *command, char **args, char **env,
		 char *program, int line_number);

/* path.c */
char *get_path(char **env);
char *find_command(char *command, char **env);

/* path_utils.c */
char *build_path(char *directory, char *command);
char *check_command(char *command);
char *search_path(char *path, char *command);

/* free_args.c */
void free_args(char **args);

#endif

