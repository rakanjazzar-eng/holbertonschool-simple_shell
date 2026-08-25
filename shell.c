#include "shell.h"

/**
 * read_line - Reads a line from standard input.
 *
 * Return: Pointer to the line string, or NULL on EOF/error.
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t nread;

	nread = getline(&line, &bufsize, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}

	if (line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}

/**
 * resolve_cmd - Resolves the full path of a command.
 * @args: Null-terminated argument array, args[0] is the command.
 * @argv0: Shell name for error messages.
 *
 * Return: Full path string, or NULL if not found.
 */
static char *resolve_cmd(char **args, char *argv0)
{
	char *cmd_path = NULL;

	if (args[0][0] == '/' || args[0][0] == '.')
	{
		if (access(args[0], X_OK) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", argv0, args[0]);
			return (NULL);
		}
		return (strdup(args[0]));
	}

	cmd_path = find_in_path(args[0]);
	if (cmd_path == NULL)
		fprintf(stderr, "%s: 1: %s: not found\n", argv0, args[0]);

	return (cmd_path);
}

/**
 * fork_and_exec - Forks a child and runs the command via execve.
 * @cmd_path: Resolved executable path.
 * @args: Null-terminated argument array.
 * @argv0: Shell name for error messages.
 *
 * Return: Exit status of the child, or 1 on abnormal termination.
 */
static int fork_and_exec(char *cmd_path, char **args, char *argv0)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}

	if (pid == 0)
	{
		if (execve(cmd_path, args, environ) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", argv0, args[0]);
			free(cmd_path);
			exit(127);
		}
	}

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

/**
 * execute_command - Resolves and executes a command without blind forking.
 * @args: Null-terminated array of arguments (args[0] is the command).
 * @argv0: Name of the shell for precise error messages.
 *
 * Return: Exit status of the child, 127 if not found.
 */
int execute_command(char **args, char *argv0)
{
	char *cmd_path = NULL;
	int status = 0;

	cmd_path = resolve_cmd(args, argv0);
	if (cmd_path == NULL)
		return (127);

	status = fork_and_exec(cmd_path, args, argv0);

	free(cmd_path);

	return (status);
}

/**
 * builtin_env - Prints all current environment variables.
 */
void builtin_env(void)
{
	int i = 0;

	if (!environ)
		return;

	while (environ[i] != NULL)
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

