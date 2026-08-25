#include "main.h"

/**
 * main - Open shell, project base.
 *
 * Return: The exit status of the last executed command.
 */
int main(void)
{
	char *buff = NULL, **args;
	size_t read_size = 0;
	ssize_t buff_size = 0;
	int exit_status = 0;

	while (1)
	{
		/* Print prompt only if connected to a terminal */
		if (isatty(STDIN_FILENO))
			printf("hsh$ ");

		buff_size = getline(&buff, &read_size, stdin);
		if (buff_size == -1 || _strcmp("exit\n", buff) == 0)
		{
			free(buff);
			break;
		}

		/* Remove trailing newline character */
		if (buff[buff_size - 1] == '\n')
			buff[buff_size - 1] = '\0';

		/* Handle the "env" Built-in command */
		if (_strcmp("env", buff) == 0)
		{
			_env();
			continue;
		}

		/* Skip empty lines safely */
		if (strlen(buff) == 0)
			continue;

		/* Split the input command into arguments array */
		args = _split(buff, " \t");
		if (args[0] == NULL)
		{
			free(args);
			continue;
		}

		/* Resolve command full path via PATH directories */
		args[0] = search_path(args[0]);

		if (args[0] != NULL)
		{
			exit_status = execute(args);
		}
		else
		{
			/* Standard UNIX shell error format for missing commands */
			fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
			exit_status = 127;

			if (!isatty(STDIN_FILENO))
			{
				free(buff);
				free(args);
				exit(127);
			}
		}
		free(args);
	}
	return (exit_status);
}

