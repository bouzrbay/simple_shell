#include "shell.h"

/**
 *
 * scan_redirection_outgoing - ...
 *
 *@arg: ...
 *
 *Return: ...
 */


char *scan_redirection_outgoing(char *arg[])
{
char *redirect = NULL;
int  increment = 0;

    while (arg[increment] != NULL)
    {
        if (strcmp(arg[increment], ">") == 0)
        {
            redirect = malloc(strlen(arg[increment + 1]) + 1);
            redirect[0] = 'w';
            redirect[1] = '\0';
            strcat(redirect, arg[increment + 1]);
            free(arg[increment]);
            free(arg[increment + 1]);    
            while (arg[increment + 2] != NULL)
            {
                arg[increment] = arg[increment + 2];
                ++increment;
            }
            arg[increment] = NULL;
        }
        else if (strcmp(arg[increment], ">>") == 0)
        {
            redirect = malloc(strlen(arg[increment + 1]) + 1);
            redirect[0] = 'a';
            redirect[1] = '\0';
            strcat(redirect, arg[increment + 1]);
            free(arg[increment]);
            free(arg[increment + 1]);    
            while (arg[increment + 2] != NULL)
            {
                arg[increment] = arg[increment + 2];
                ++increment;
            }
            arg[increment] = NULL;
        }
        ++increment;
    }
    return (redirect);
}
