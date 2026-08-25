#include "shell.h"

/**
 * token - Breaks an incoming string into individual command arguments.
 * @line: The raw stream array retrieved from the input.
 *
 * Return: A pointer block holding string elements, or NULL if it fails.
 */
char **token(char *line)
{
	char **args;
	char *token_ptr;
	int i;

	i = 0;
	args = malloc(sizeof(char *) * 64);
	if (!args)
		return (NULL);

	token_ptr = strtok(line, " \t\n");
	while (token_ptr != NULL)
	{
		args[i] = token_ptr;
		i++;
		token_ptr = strtok(NULL, " \t\n");
	}
	args[i] = NULL;
	return (args);
}

/**
 * print_env - Loops and outputs the loaded system environment variables.
 *
 * Return: Void.
 */
void print_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * main - Primary loop driver that controls the shell terminal.
 * @argc: Number of arguments passed to the program (unused).
 * @argv: Array of dynamic startup string pointers.
 *
 * Return: Zero if completed successfully.
 */
int main(int argc, char **argv)
{
	char *line;
	size_t len;
	ssize_t nread;
	char **args;
	int last_status;

	(void)argc;
	line = NULL;
	len = 0;
	last_status = 0;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(last_status);
		}
		args = token(line);
		if (args == NULL || args[0] == NULL)
		{
			free(args);
			continue;
		}
		if (strcmp(args[0], "exit") == 0)
		{
			free(args);
			free(line);
			exit(last_status);
		}
		if (strcmp(args[0], "env") == 0)
		{
			print_env();
			free(args);
			continue;
		}
		last_status = execute(args, argv[0]);
		free(args);
	}
	free(line);
	return (0);
}

