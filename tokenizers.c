#include "shell.h"
#include <string.h>
#include <stdlib.h>

/* Delimiters: space and tab */
#define DELIMS " \t"

/**
 * count_tokens - Count how many tokens exist in the string
 * @s: The input string
 *
 * This function scans through the string and counts the
 * number of substrings separated by spaces or tabs.
 * It does not modify the original string.
 *
 * Return: Number of tokens
 */
size_t count_tokens(const char *s)
{
	const char *p = s;
	size_t n = 0;

	if (p == NULL)
		return (0);

	while (*p != '\0')
	{
		/* Skip leading spaces/tabs */
		while (*p == ' ' || *p == '\t')
			p++;

		if (*p == '\0')
			break;
		/* Found a token */
		n++;

		/* Move to the end of this token */
		while (*p != '\0' &&  *p != ' ' && *p != '\t')
			p++;
	}
	return (n);
}

/**
 * tokenize_line - Split a string into tokens(argv)
 * @line: The input line, which will be modified by strtok
 *
 * This function uses strtok to break the line into tokens
 * based on spaces/tabs. It returns a NULL-terminated array
 * of strings similar to argv. The array must be freed with
 * free_argv(), but the tokens themselves should not be freed.
 *
 * Return: A pointer to an array of string pointers (argv),
 *         or NULL if no tokens are found.
 */
char **tokenize_line(char *line)
{
	size_t ntok, i;
	char **argv;
	char *tok;

	if (line == NULL)
		return (NULL);

	/* Count tokens first */
	ntok = count_tokens(line);
	if (ntok == 0)
		return (NULL);

	/* Allocate space for array of pointers */
	argv = (char **)malloc((ntok + 1) * sizeof(char *));
	if (argv == NULL)
		return (NULL);

	/* Use strtok to extract tokens */
	tok = strtok(line, DELIMS);
	i = 0;
	while (tok != NULL && i < ntok)
	{
		argv[i++] = tok;
		tok = strtok(NULL, DELIMS);
	}
	argv[i] = NULL; /* NULL-terminate the array */

	return (argv);
}


/**
 * free_argv - Free the token array
 * @argv: The array returned by tokenize_line
 *
 * This function frees only the array itself, not the
 * individual strings, because they are part of the original line.
 */
void free_argv(char **argv)
{
	if (argv != NULL)
		free(argv);
}
