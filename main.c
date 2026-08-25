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
	char *args[1024]; /* تعريف مصفوفة المؤشرات بشكل صحيح وسليم */
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
		while (token != NULL && i < 1023)
		{
			args[i++] = token;
			token = strtok(NULL, " \t\n");
		}
		args[i] = NULL;

		if (args[0] == NULL)
			continue;

		/* معالجة الأمر المدمج exit */
		if (strcmp(args[0], "exit") == 0)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}

		/* معالجة الأمر المدمج env */
		if (strcmp(args[0], "env") == 0)
		{
			print_env();
			continue;
		}

		/* البحث في الـ PATH والتحقق قبل الـ fork */
		actual_path = find_path(args[0]);
		if (actual_path == NULL)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);

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

