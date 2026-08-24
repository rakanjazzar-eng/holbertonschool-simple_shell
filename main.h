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

char *getln(void);
char **formatln(char *ln);
char *compose(char *token, char *val);
void launch_process(char **command);
void search_exe(char **command);
char *_getenv(char *name);
void handler_function(int i);

#endif /* MAIN_H */