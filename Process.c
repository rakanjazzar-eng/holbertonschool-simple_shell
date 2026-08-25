#include "main.h"

/**
 * _getenv - Custom implementation to retrieve environment variables.
 * @name: Name of the environment variable.
 *
 * Return: Pointer to the variable's value, or NULL if not found.
 */
char *_getenv(const char *name)
{
	int i = 0;
	size_t len = strlen(name);

	if (!environ || !name)
		return (NULL);

	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
		i++;
	}
	return (NULL);
}

/**
 * find_path - Searches for a command across the directories in PATH.
 * @command: The command name to look up.
 *
 * Return: Full path string if found, or NULL if it doesn't exist.
 */
char *find_path(char *command)
{
	char *path_env = _getenv("PATH");
	char *path_copy, *token, *full_path;
	struct stat st;

	if (!command || strlen(command) == 0)
		return (NULL);

	/* If command contains a slash '/', it's a direct path, check it directly */
	if (strchr(command, '/') != NULL)
	{
		if (stat(command, &st) == 0)
			return (strdup(command));
		return (NULL);
	}

	if (!path_env || strlen(path_env) == 0)
		return (NULL);

	path_copy = strdup(path_env);
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		full_path = malloc(strlen(token) + strlen(command) + 2);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", token, command);
		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
 * launch_process - Forks the current process and executes a command.
 * @command: NULL-terminated array of arguments.
 * @prog_name: Name of the executable for error printing.
 * @actual_path: The resolved full path of the command.
 *
 * Return: Void.
 */
void launch_process(char **command, char *prog_name, char *actual_path)
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
		if (execve(actual_path, command, environ) == -1)
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

