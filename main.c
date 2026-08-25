#include "shell.h"

/**
 * tokenize_input - Parses the command line string into separate arguments.
 * @line: The raw input string provided by the user.
 * @args: The destination pointer array to store the parsed tokens.
 */
void tokenize_input(char *line, char **args)
{
	char *token;
	int i = 0;

	token = strtok(line, " \t");
	while (token != NULL && i < 63)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " \t");
	}
	args[i] = NULL;
}

/**
 * main - Core processing loop for the command line interpreter.
 * @argc: Command line argument count (unused).
 * @argv: Array of invocation argument strings.
 *
 * Return: Status code of the final executed operation.
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	char *args[64];
	size_t len = 0;
	int status = 0;
	int e;

	(void)argc;

	while (1)
	{
		display_prompt();
		if (getline(&line, &len, stdin) == -1)
		{
			free(line);
			exit(status);
		}
		line[strcspn(line, "\n")] = '\0';
		tokenize_input(line, args);

		if (args[0] == NULL)
			continue;

		/* Intercept the built-in exit statement */
		if (strcmp(args[0], "exit") == 0)
		{
			free(line);
			exit(status);
		}

		/* Intercept the built-in env statement */
		if (strcmp(args[0], "env") == 0)
		{
			e = 0;
			while (environ[e] != NULL)
			{
				printf("%s\n", environ[e]);
				e++;
			}
			continue;
		}
		status = execute_command(args, argv[0]);
	}
	return (status);
}

