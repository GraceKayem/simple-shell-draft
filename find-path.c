#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shell.h"

extern char **environ;
/**
 * find_command - Simple shell 0.2
 * @command: Handle the PATH
 * Return: malloc'd full path if found (caller must free), or NULL if not found
 */
char *find_command(char *command)
{
    int length;
    char *path, *path_copy, *full_path, *directory;
    
    if (command == NULL)
    {
       return (NULL);
    }
   
   /*checking the first index of a command -- Absolute vs relative path check*/
     if (*command == '/' || *command == '.')
     {
        if (access(command, X_OK) == 0)
        {
            return (strdup(command));
	}
	return (NULL);
     }
     
    /* Get PATH */
    path = getenv("PATH");
    printf("PATH: %s\n", path);
    if (path == NULL)
    {
        return (NULL);
    }
    
    /*making a copy of the path to avoid affecting the path directly*/
    path_copy = strdup(path);
    /*checking if path has been defined*/
    if (path_copy == NULL)
    {
        return (NULL);
    }
    
    /*Tokenizing*/
    directory = strtok(path_copy, ":");
    while (directory != NULL)
    {
        /*determine the length of the directory*/
        length = strlen(directory) + strlen (command) + 2;
        full_path = malloc(sizeof(char) * length);
        if (full_path == NULL)
        {
            free(path_copy);
            return (NULL);
        }
        
        snprintf(full_path, length, "%s/%s", directory, command);
        printf("Trying: %s\n", full_path);
        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return (full_path);
        }
        
        free(full_path);
        /*Tokenizing*/
        directory = strtok(NULL, ":");
    }
    free(path_copy);
    /*PATH not found*/
    return (NULL); 
}

/**
 * execute_command - fork must not be called if the command doesn’t exist
 * @command: command name
 * @args: argument vector (argv)
 * Return: 0 if success, 1 if failure
 */
int handle_command(char *command, char **args)
{
    char *full_path;
    pid_t pid;

    /*debugging*/
    printf("Debug: Command='%s', args[0]='%s'\n", command, args[0]);
    
    full_path = find_command(command);
    if (full_path == NULL)
    {
        fprintf(stderr, "%s: Command not found\n", command);
        return (1);
    }

    pid = fork();
    if (pid == -1) 
    {
        perror("Error:");
        free(full_path);
        return (1);
    }
    
    if (pid == 0) 
    {
	printf("Debug: Executing command at path: %s\n", full_path);
	execve(full_path, args, environ);
        perror("execve");
        exit(1);
    }
    else
    {
        wait(NULL);
    }
    
    free(full_path);
    return (0);
}
