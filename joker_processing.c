#include "shell.h"

/**
 *
 *joker_processing - ...
 *
 *@arg: ...
 *
 */

void joker_processing(char *arg[])
{

char *arg_list_tmp[32];

    int increment = 0;
    int increment_tmp = 0;
    while (arg[increment] != NULL)
    {
        char *tmp = strstr(arg[increment], "*");
        if (tmp != NULL)
        {
            glob_t g;
            int return_glob = glob(tmp , 0, NULL, &g);
            if (return_glob == 0)
            {
                int loop;
                for (loop = 0; loop < g.gl_pathc; ++loop)
                {
                    arg_list_tmp[increment_tmp] = strdup(g.gl_pathv[loop]);
                    ++increment_tmp;
                }
                free(arg[increment]);
            }
            else
            {
                arg_list_tmp[increment_tmp] = arg[increment];
                ++increment_tmp;
            }
            globfree(&g);
        }
        else
        {
            arg_list_tmp[increment_tmp] = arg[increment];
            ++increment_tmp;
        }
        ++increment;
    }
    arg_list_tmp[increment_tmp] = NULL;
    increment = 0;
    while (arg_list_tmp[increment] != NULL)
    {
        arg[increment] = arg_list_tmp[increment];
        ++increment;
    }
    arg[increment] = NULL;
}
