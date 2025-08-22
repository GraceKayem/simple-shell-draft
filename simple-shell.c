#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "shell.h"
#include "builtins.h"

/**
 * only_spaces - searches a string to check for only_spaces
 * @line: string to check
 * Return: 1 if line is only spaces or tabs, 0 if other characters found
 */
int only_spaces(char *line)
{
	int i = 0;

	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

/**
 * main - entrypoint to simple shell
 * @ac: Number of args passed to the program
 * @av: Array of arguments
 * Return: 0
 */
extern char **environ;
char *find_command(char *command);

int main(int ac, char **av)
{
	char *line;
	size_t buffer_size = 256;
	ssize_t nread;
	int child;
	int tty = 1, exec_return = 0;
	int builtin_status = 0;
	(void)ac;
	line = malloc(buffer_size + 1);
	tty = isatty(STDIN_FILENO);

	while (1)
	{
		if (tty == 1)
			printf("#cisfun$: ");
		nread = getline(&line, &buffer_size, stdin);
		
		if (nread == -1)
		{
			break;
		}
		line[strcspn(line, "\n")] = '\0';
		if (line[0] == ' ')
		{
			if (only_spaces(line) == 1)
				break;
		}
		av = tokenize_line(line);
		builtin_status = handle_builtin(av);

		if (builtin_status == -1)
		{
			free_argv(av);
			free(line);
			exit(0);
		}
		else if (builtin_status == 1)
		{
			free_argv(av);
			continue;
		}

		
                pid_t pid;
		if (tokens[0] == NULL)
		{
			free(line);
			free(input_copy);
			free(token);
			continue;
		}
		

		char *cmd_path = find_command(tokens[0]);

		pid_t = fork();
		if (pid < 0)
		{
			perror("Erreor")
			free(line);
			free(input_copy);
			free(token);
			continue;
		}

		if (pid == 0)
		{
			if (execve(cmd_path, tokens, environ) == -1)
			{
				perror("command not found");
			}
		}
		else 
		{
			waitpid(pid, &status, 0);
		}
		free(line);
		free(input_copy);
		free(token);
		
	}

	free(line);
	return (exec_return);
}
