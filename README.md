# holbertonschool-simple_shell
holbertonschool-simple_shell
Description

simple_shell (compiled as hsh) is a UNIX command line interpreter, written as a low-level, educational re-implementation of a subset of /bin/sh. It is developed as part of the Holberton School / ALX System Engineering & DevOps curriculum.

The project reproduces the core behaviour of a shell: printing a prompt, reading a command line, parsing it, locating the requested program (using the PATH environment variable when needed), forking a child process, and executing the program with execve, then waiting for it to finish before printing the prompt again.

Compilation

The project is compiled on Ubuntu 20.04 LTS with gcc, using the following flags:

sh
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
Usage

hsh can be used in two modes.

Interactive mode
sh
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
Non-interactive mode

Commands can also be piped into the shell:

sh
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c
$

If no command is entered before the end of file (Ctrl+D), the shell exits cleanly, printing a newline in interactive mode (matching the behaviour of sh).

Environment

Our shell inherits the environment of the process that started it, and supports built-ins that read and manipulate it (see env below, added in a later task).

Built-in commands

Built-in commands are implemented directly by the shell instead of being looked up on PATH. As they are added throughout the project, they will be documented here and in the man page. Planned built-ins include:

exit — exits the shell
env — prints the current environment
setenv — initializes a new environment variable, or modifies an existing one
unsetenv — removes an environment variable
cd — changes the current directory
Error handling

When a command cannot be found or executed, hsh prints an error message on stderr in the same format as sh, except that the program name printed is the value of argv[0] used to invoke the shell (e.g. ./hsh, ./././hsh, ...), instead of sh:

sh
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
Testing

Manual tests can be run by piping commands into hsh and comparing the output (stdout, stderr and exit status) against /bin/sh. A test suite, contributed by the cohort, will be added under a dedicated task.

Repository
File	Description
README.md	This file
man_1_simple_shell	Man page for hsh, section 1
AUTHORS	List of individuals who contributed content
Authors

See the AUTHORS file.

License

This project is part of the Holberton School / ALX curriculum and is provided for educational purposes.