#include "main.h"
 
char *prog_name;
 
/**
 * main - entry point of the simple shell
 * @argc: argument count (unused)
 * @argv: argument vector, argv[0] is the name the shell was invoked with
 *
 * Return: always 0
 */
int main(int argc, char **argv)
{
	char *line;
	char *args[2];
	int interactive = isatty(STDIN_FILENO);
 
	(void)argc;
	prog_name = argv[0];
 
	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
 
		line = getln();
		if (line == NULL)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
 
		if (line[0] == '\0')
		{
			free(line);
			continue;
		}
 
		args[0] = line;
		args[1] = NULL;
		launch_process(args);
		free(line);
	}
 
	return (0);
}
