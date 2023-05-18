#include "shell.h"

/**
 *release_arg - ...
 *
 *@arg: ...
 *
 */

void release_arg(char *arg[])
{

int increment=0;

while (arg[increment] != NULL)
{
free(arg[increment]);

increment++;

}

}