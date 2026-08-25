#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char **environ;

int launch_process(char **command, char *prog_name, char *actual_path);
void run_shell(char *prog_name);
char *_getenv(const char *name);
char *find_path(char *command);
void print_env(void);

#endif /* MAIN_H */

