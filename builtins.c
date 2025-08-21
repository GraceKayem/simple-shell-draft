#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

extern char **environ;

/**
 * handle_builtin - check and executes built-in commands
 * @argv: parsed command arguments
 * Return: -1 if shell should exit, otherwise 0
 */

int handle_builtin(char **argv)
{
	int i;

	if (argv[0] == NULL)
		return (0);

	if (strcmp(argv[0], "exit") == 0)
		return (-1);

	if (strcmp(argv[0], "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
			printf("%s\n", environ[i]);
		return (1);
	}

	return (0);
}
