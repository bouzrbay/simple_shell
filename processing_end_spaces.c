#include "shell.h"

/**
 *processing_end_spaces - ...
 *
 *@string_to_process: ...
 *
 */

void processing_end_spaces(char *string_to_process)
  
{
while (string_to_process[strlen(string_to_process) - 1] == ' ')
{
string_to_process[strlen(string_to_process) - 1] = '\0';
}
}
