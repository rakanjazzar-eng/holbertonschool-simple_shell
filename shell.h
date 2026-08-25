#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char **environ;

/* Core Core Functions */
char *read_line(void);
char **split_line(char *line);
int execute_command(char **args, char *argv0);
void builtin_env(void);
char *find_in_path(char *cmd);

#endif /* SHELL_H */

