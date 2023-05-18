#include "shell.h"

/**
 *
 * processing_beginning_spaces - ...
 *
 *@string_to_process: ...
 *
 */

void processing_beginning_spaces(char *string_to_process)
{
  char *new_string = string_to_process;
  while (new_string[0] == ' ')
    {
      ++new_string;
    }
  memmove(string_to_process, new_string, strlen(new_string) + 1);
}
