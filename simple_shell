#include "shell.h"

/**
 * variable_management - ...
 *
 *@arg: ...
 *@argv: ...
 *
 */

void variable_management(char* arg[], char **argv)
{

int increment = 0;

    while (arg[increment] != NULL)
    {
        char *string_to_scan = arg[increment];
        if (string_to_scan[0] == '$') 
        {
            int detection = 0;
            char *endptr = NULL;
            int integer = strtol(arg[increment] + 1, &endptr, 10);
            if (strcmp(endptr, "") != 0)
	    integer = -1;
            if (integer != -1)
            {
                if (integer + 1 <= global_argc)
                {
                    free(arg[increment]);
                    arg[increment] = strdup(argv[integer]);
                    detection = 1;
                }
            }
            else
            {
                environment *list = var_environment;
                while (list != NULL)
                {
                    if (strcmp(list ->name, string_to_scan + 1) == 0)
                    {
                        free(arg[increment]);
                        arg[increment] = strdup(list -> value);
                        detection = 1;
                    }
                    list = list -> next;
                }
            }
            if (detection == 0)
            {
                free(arg[increment]);
                arg[increment] = strdup("");
            }
        }
        ++increment;
    }
}
