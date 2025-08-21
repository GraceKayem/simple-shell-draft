#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>

/**
 * count_tokens - Count the number of tokens in a string
 * @s: The input string (will not be modified)
 *
 * Return: The number of tokens found.
 */
size_t count_tokens(const char *s);

/**
 * tokenize_line - Split a line into tokens (like argv)
 * @line: The input string. This function modifies the string in-place.
 *
 * Return: A NULL-terminated array of string pointers (argv-style).
 *         The array itself must be freed with free_argv().
 *         Do not free argv[i] because they point into 'line'.
 */
char **tokenize_line(char *line);

/**
 * free_argv - Free the array returned by tokenize_line
 * @argv: The array to free
 */
void free_argv(char **argv);
int only_spaces(char *line);
int handle_builtin(char **argv);
char *find_command(char *command);
int handle_command(char *command, char **args);

#endif
