#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


/* prompt.c */
char *read_command(void);

/* token.c */
char *trim_command(char *command);
int tokenize(char *command, char *args[]);

/* builtins.c */
int handle_builtin(char **args, char **envp, int status);

/* process.c */
int process_command(char **args, char **envp, int status,
		int line_number, char *line);

/* env.c */
void print_environment(char **envp);

/* execute.c */
int execute_command(char **args, char **envp, char *command_path);

/* fork.c */
int create_process(char **args, char **envp, char *command_path);

/* wait.c */
int wait_for_process(pid_t pid);

/* path.c */
char *get_path(char **envp);
char *build_path(char *directory, char *command);
char *search_path(char *path, char *command);
char *find_command(char *command, char **envp);

#endif
