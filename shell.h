#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/* Prototypes for core shell mechanics */
char **token(char *line);
int execute(char **args, char *prog);
char *find_path(char *cmd);
char *_getenv(char *name);

#endif /* SHELL_H */

