#include "shell.h"

/**
 *str_replaced - ...
 *
 *@string: ...
 *@research: ...
 *@replaced: ...
 *
 */

void str_replaced(char *string, char* research, char *replaced)
{
  int nbre = 0;

  char *p = string;
  char *tmp = strstr(p, research);
  while (tmp != NULL)
    {
      ++nbre;
      p = tmp + strlen(research);
      tmp = strstr(p, research);
    }
  if (nbre > 0)
    {
      char *copy_string = malloc(strlen(string)-(strlen(research) * nbre) + (strlen(replaced) * nbre) + 1);
      copy_string[0]='\0';
      char *p = string;
      char *tmp = strstr(p, research);
      while (tmp != NULL)
	{
	  strncat(copy_string, p, tmp-p);
	  strcat(copy_string, replaced);
	  p = tmp + strlen(research);
	  tmp = strstr(p,research);
	}
      strcat(copy_string, p);
      strcpy(string, copy_string);
      free(copy_string);
    }
}
