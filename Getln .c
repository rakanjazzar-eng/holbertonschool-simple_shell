#include "main.h"
 
/**
 * getln - reads a line of input from standard input, trimming any
 * leading and trailing whitespace (spaces, tabs, newline)
 *
 * Return: a pointer to the dynamically allocated, trimmed line, or
 * NULL if end of file was reached
 */
char *getln(void)
{
	char *line = NULL;
	char *start;
	size_t len = 0, end;
	ssize_t nread;
 
	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}
 
	start = line;
	while (*start == ' ' || *start == '\t')
		start++;
 
	end = strlen(start);
	while (end > 0 && (start[end - 1] == '\n' || start[end - 1] == ' ' ||
			start[end - 1] == '\t' || start[end - 1] == '\r'))
		end--;
	start[end] = '\0';
 
	if (start != line)
		memmove(line, start, end + 1);
 
	return (line);
}