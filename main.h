#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

extern char **environ;
extern char *prog_name;

#define PROMPT "($) "



void launch_process(char **command,char *prog_name);
void run_shell(char *prog_name);
char *_getenv(const char *name);
char *find_path(char *command);

#endif /* MAIN_H */
