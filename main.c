#include "main.h"



/**
 * main - entry point of the simple shell
 * @argc: argument count (unused)
 * @argv: argument vector, argv[0] is the name the shell was invoked with
 *
 * Return: always 0
 */
int main(int argc, char **argv)
{
	
	(void)argc;
    run_shell(argv[0]);
	return (0);
}
/**
 * run_shell - main loop for reading and processing commands
 * @prog_name: name of the executable for error printing
 */
void run_shell(char *prog_name)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *args[1024];
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

        if (args[0] == NULL)
            continue;

       launch_process(args, prog_name);
    }

    free(line);
}