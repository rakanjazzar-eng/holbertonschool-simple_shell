#include "shell.h"

/**
 * _getenv - Searches the local ecosystem array for a targeted item.
 * @name: Identifier variable name to query.
 *
 * Return: Text string matching the value, or NULL if nonexistent.
 */
char *_getenv(char *name)
{
	int i;
	int len;

	len = strlen(name);
	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], name, len) == 0)
		{
			if (environ[i][len] == '=')
				return (environ[i] + len + 1);
		}
	}
	return (NULL);
}

/**
 * find_path - Cycles through system directories to discover binaries.
 * @cmd: Standalone application name to map.
 *
 * Return: Resolved full path target, or NULL if unfound.
 */
char *find_path(char *cmd)
{
	char *path;
	char *path_copy;
	char *dir;
	char *full_path;
	struct stat st;

	if (strchr(cmd, '/'))
	{
		if (stat(cmd, &st) == 0)
			return (strdup(cmd));
		return (NULL);
	}
	path = _getenv("PATH");
	if (path == NULL)
		return (NULL);
	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		full_path = malloc(strlen(dir) + strlen(cmd) + 2);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, cmd);
		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

