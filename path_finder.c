#include "shell.h"

/**
 * _getenv - Extracts the value of a specified environment variable.
 * @name: The identity key of the environment variable to look up.
 *
 * Return: A pointer directly to the variable's value data, or NULL if absent.
 */
char *_getenv(const char *name)
{
	int i = 0;
	size_t len;

	if (name == NULL || environ == NULL)
		return (NULL);

	len = strlen(name);
	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
	}
	return (NULL);
}

/**
 * get_location - Resolves and extracts the absolute system path of a command.
 * @cmd: The targeted standalone command name to be located.
 *
 * Return: A newly allocated string containing the total path, or NULL on error.
 */
char *get_location(char *cmd)
{
	char *path, *p_cpy, *tok, *f_path;
	struct stat st;

	if (cmd == NULL)
		return (NULL);
	if (strchr(cmd, '/'))
	{
		if (stat(cmd, &st) == 0)
			return (strdup(cmd));
		return (NULL);
	}
	path = _getenv("PATH");
	if (!path || *path == '\0')
		return (NULL);
	p_cpy = strdup(path);
	if (!p_cpy)
		return (NULL);
	tok = strtok(p_cpy, ":");
	while (tok)
	{
		f_path = malloc(strlen(tok) + strlen(cmd) + 2);
		if (!f_path)
		{
			free(p_cpy);
			return (NULL);
		}
		sprintf(f_path, "%s/%s", tok, cmd);
		if (stat(f_path, &st) == 0)
		{
			free(p_cpy);
			return (f_path);
		}
		free(f_path);
		tok = strtok(NULL, ":");
	}
	free(p_cpy);
	return (NULL);
}

