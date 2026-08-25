#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

extern char **environ;

/* Function prototypes for core system routines */
void display_prompt(void);
int execute_command(char **args, char *prog_name);
char *_getenv(const char *name);
char *get_location(char *cmd);
void tokenize_input(char *line, char **args);

#endif /* SHELL_H */

