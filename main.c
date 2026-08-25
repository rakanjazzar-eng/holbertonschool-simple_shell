#include "shell.h"

/**
 * main - Entry point for the simple UNIX command interpreter.
 * @argc: Argument count (unused).
 * @argv: Argument vector, argv[0] used for error messages.
 *
 * Return: The last command exit status.
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

		/* 2. Read line and handle EOF (Ctrl+D) condition */
		line = read_line();
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

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

		/* 4. Built-in: exit */
		if (strcmp(args[0], "exit") == 0)
		{
			free(line);
			free(args);
			exit(last_status);
		}

		/* 5. Built-in: env */
		if (strcmp(args[0], "env") == 0)
		{
			builtin_env();
			last_status = 0;
			free(line);
			free(args);
			continue;
		}

		/* 6. Execute external command via PATH and fork */
		last_status = execute_command(args, argv[0]);

		free(line);
		free(args);
	}

	return (last_status);
}

