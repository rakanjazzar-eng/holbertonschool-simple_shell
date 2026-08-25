#include "shell.h"

/**
 * execute - Launches a process block to handle system calls.
 * @args: Array containing the command text along with variables.
 * @prog: The binary name of our shell for generating logs.
 *
 * Return: Numeric exit state status code from the active program.
 */
int execute(char **args, char *prog)
{
	pid_t pid;
	int status;
	char *cmd;

	cmd = find_path(args[0]);
	if (cmd == NULL)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", prog, args[0]);
		return (127);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd);
		return (1);
	}
	if (pid == 0)
	{
		if (execve(cmd, args, environ) == -1)
		{
			perror("execve");
			free(cmd);
			exit(1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		free(cmd);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}

