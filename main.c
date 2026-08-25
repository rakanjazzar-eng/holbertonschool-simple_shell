#include "main.h"

/**
 * run_shell - Main loop for reading and processing commands.
 * @prog_name: Name of the executable for error printing.
 *
 * Return: Void.
 */
void run_shell(char *prog_name)
{
	char *line = NULL, *actual_path = NULL;
	size_t len = 0;
	ssize_t nread;
	char *args[1024];
	char *token;
	int i;

	while (1)
	{
		/* Print prompt only if standard input is a terminal */
		if (isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, ":) ", 3);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}

		/* Tokenize the input line into arguments */
		i = 0;
		token = strtok(line, " \t\n");
		while (token != NULL)
		{
			args[i++] = token;
			token = strtok(NULL, " \t\n");
		}
		args[i] = NULL;

		/* Skip empty lines where only Enter was pressed */
		if (args[0] == NULL)
			continue;

		/* Check if command exists in PATH before calling fork */
		actual_path = find_path(args[0]);
		if (actual_path == NULL)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
			continue;
		}

		/* Execute the verified command path */
		launch_process(args, prog_name, actual_path);
		free(actual_path);
	}
	free(line);
}

/**
 * main - Entry point of the simple shell.
 * @argc: Argument count (unused).
 * @argv: Argument vector, argv[0] is the shell invocation name.
 *
 * Return: Always 0 (Success).
 */
int main(int argc, char **argv)
{
	(void)argc;

	run_shell(argv[0]);
	return (0);
}

