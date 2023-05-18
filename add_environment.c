#include "shell.h"

/**
 *add_environment - ...
 *
 *@name_variable: ...
 *@value_variable: ...
 *
 */

void add_environment(char *name_variable, char *value_variable)
{
 environment *liste=var_environment;

  int test=0;
  if (liste!=NULL)
    {
      while (liste->next!=NULL)
	{
	  if (strcmp(name_variable, liste->name) == 0)
	    {
	      free(liste->value);
	      liste->value = strdup(name_variable);
	      test = 1;
	    }
	  liste = liste->next;
	}
    }

  if (test==0)
    {
      environment *new_env = malloc(sizeof(environment));
      new_env->name = strdup(name_variable);
      new_env->value = strdup(value_variable);
      new_env->next = NULL;
      liste = var_environment;
      if (liste != NULL)
	{
	  while (liste->next != NULL)
	    {
	      liste = liste->next;
	    }
	  liste->next = new_env;
	}
      else
	{
	  var_environment = new_env;
	}
    }
}
