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
        if (strlen(directory) == 0)
                {
                        directory = ".";
                }
        /*determine the length of the directory*/
        length = strlen(directory) + strlen (command) + 2;
        full_path = malloc(sizeof(char) * length);
        if (full_path == NULL)
        {
            free(path_copy);
            return (NULL);
        }
        
        sprintf(full_path, "%s/%s", directory, command);

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
