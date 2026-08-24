#include "main.h"
 
/**
 * launch_process - forks the current process and executes a command
 * @command: NULL-terminated array of arguments; command[0] is the
 * path of the program to execute
 *
 * Return: void
 */
void launch_process(char **command)
{
	pid_t pid;
	int status;
 
	pid = fork();
	if (pid == -1)
	{
		perror(prog_name);
		return;
	}
 
	if (pid == 0)
	{
		if (execve(command[0], command, environ) == -1)
		{
			perror(prog_name);
			_exit(127);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			perror(prog_name);
	}
}
 


