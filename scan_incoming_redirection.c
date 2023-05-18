#include "shell.h"

/**
 *scan_incoming_redirection - ...
 *
 *@arg: ...
 *
 *Return: ...
 */

char *scan_incoming_redirection(char *arg[])
{

char *redirect = NULL;
int  increment = 0;

    while (arg[increment] != NULL)
    {
        if (strcmp(arg[increment], "<") == 0)
        {
            redirect = arg[increment + 1];
            free(arg[increment]);        
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
