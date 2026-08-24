
#include "main.h"
 
/**
 * getln - reads a line of input from standard input
 *
 * Return: a pointer to the dynamically allocated line (without its
 * trailing newline), or NULL if end of file was reached
 */
char *getln(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
 
	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}
 
	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';
 
	return (line);
}
 