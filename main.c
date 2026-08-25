#include "shell.h"

/**
 * main - Entry point for the simple UNIX shell.
 * @argc: Argument count (unused).
 * @argv: Argument vector, argv[0] used for error printing.
 *
 * Return: Last command exit status.
 */
int main(int argc __attribute__((unused)), char **argv)
{
	char *line = NULL;
	char **args = NULL;
	int last_status = 0;

	while (1)
	{
		/* 1. Display prompt only in interactive mode */
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "($) ", 4);
			fflush(stdout);
		}

		/* 2. Read line and handle EOF (Ctrl+D) gracefully */
		line = read_line();
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		/* Skip completely empty lines */
		if (line[0] == '\0')
		{
			free(line);
			continue;
		}

		/* 3. Tokenize input line into arguments array */
		args = split_line(line);
		if (args == NULL || args[0] == NULL)
		{
			free(line);
			free(args);
			continue;
		}

		/* 4. Handle built-in "exit" command */
		if (strcmp(args[0], "exit") == 0)
		{
			free(line);
			free(args);
			exit(last_status);
		}

		/* 5. Handle built-in "env" command */
		if (strcmp(args[0], "env") == 0)
		{
			print_env();
			last_status = 0;
			free(line);
			free(args);
			continue;
		}

		/* 6. Execute normal command and update exit status */
		last_status = execute_command(args, argv[0]);

		free(line);
		free(args);
	}

	return (last_status);
}

