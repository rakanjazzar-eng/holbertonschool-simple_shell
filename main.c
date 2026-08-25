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
	char *args;
	char *token;
	int i;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, "($) ", 4);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}

		i = 0;
		token = strtok(line, " \t\n");
		while (token != NULL)
		{
			args[i++] = token;
			token = strtok(NULL, " \t\n");
		}
		args[i] = NULL;

		if (args == NULL)
			continue;

		/* 1. Handling the "exit" Built-in command */
		if (strcmp(args, "exit") == 0)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}

		/* 2. Handling the "env" Built-in command */
		if (strcmp(args, "env") == 0)
		{
			print_env();
			continue;
		}

		/* 3. Normal commands handling via PATH and fork */
		actual_path = find_path(args);
		if (actual_path == NULL)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args);
			
			/* If non-interactive mode and command not found, exit with 127 */
			if (isatty(STDIN_FILENO) != 1)
			{
				free(line);
				exit(127);
			}
			continue;
		}

		launch_process(args, prog_name, actual_path);
		free(actual_path);
	}
	free(line);
}

/**
 * main - Entry point of the simple shell.
 * @argc: Argument count (unused).
 * @argv: Argument vector, argv is the shell invocation name.
 *
 * Return: Always 0 (Success).
 */
int main(int argc, char **argv)
{
	(void)argc;

	run_shell(argv);
	return (0);
}

