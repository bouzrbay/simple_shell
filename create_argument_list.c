#include "shell.h"

/**
 * create_argument_list - ...
 *
 *@arg: ...
 *@cmd: ...
 *
 */

void create_argument_list(char *arg[], char *cmd)
{

int loop, increment, length;
char *separator = " ";

for (loop = 0; loop<32; ++loop)
{
arg[loop] = NULL;
}
length = strcspn(cmd, " \"");
arg[0] = strndup(cmd, length);
cmd = cmd + length;
increment = 1;

while (strlen(cmd) > 0)
{

if (cmd[0] == ' ')
++cmd;

if (cmd[0] == '"')
separator = "\"";

if (strcmp(separator, "\"") == 0)
++cmd;

length = strcspn(cmd, separator);
arg[increment] = strndup(cmd, length);
cmd = cmd + length;
if (strcmp(separator, "\"") == 0)
++cmd;
++increment;
}
}
