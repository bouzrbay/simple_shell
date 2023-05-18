#include "shell.h"

/**
 * line_processing - ...
 *
 *@argv: ...
 *
 */

void line_processing(char **argv);
{
  treatment_beginning_spaces(buffer);
  processing_end_spaces(buffer);
  if (buffer[0] == '#')
    {
    }
  else if (strncmp(buffer, "if", 2) == 0)
    {
      char *reading=buffer;
      int loop=0;
      environment *var_if = malloc(sizeof(environment));
      var_if->nom = malloc(4);
      sprintf(var_if->nom, "%d", boucle);
      var_if->value = strdup(buffer);
      var_if->next = NULL;
      if (strncmp(buffer, "if [", 4) != 0)
	{
	  fprintf(stderr, "%s : Syntax error\n", buffer);
	  exit(EXIT_FAILURE);
	}
      char *test_fin=strstr(buffer,"]");
      if (strcmp(test_fin, "]") != 0 && strcmp(test_fin, "] ") != 0)
	{
	  fprintf(stderr,"%s : Syntax error\n", buffer);
	  exit(EXIT_FAILURE);
	}
      char *formula = strdup(buffer);
      str_replaced(formula, "if [", "");
      str_replaced(formula, "]", "");
      str_replaced(formula, " ", "");
      str_replace(formula, "\"", "");
      int returne = strcspn(formula, "=");
      if (returne == strlen(formula))
	{
	  fprintf(stderr,"%s : Syntax error\n",buffer);
	  exit(EXIT_FAILURE);
	}
      char *arg_list_temp[32];
      arg_list_temp[0] = strndup(formula, returne);
      arg_list_temp[1] = strdup(formula + returne + 1);
      arg_list_temp[2] = NULL;
      variable_management(arg_list_temp, argv);
      int test = strcmp(arg_list_temp[0], arg_list_temp[1]);
      free(arg_list_temp[1]);
      free(arg_list_temp[0]);
      free(formula);
      environment *list_var_if = var_if;
      environment *list = list_var_if;
      while (reading != NULL)
	{
	  reading = fgets(buffer, 150, file);
	  treatment_beginning_spaces(buffer);
	  if (reading == NULL)
	    break;
	  if (buffer[strlen(buffer) - 1 ] == '\n')
	    buffer[strlen(buffer) - 1] = '\0';
	  if (strncmp(buffer, "fi", 2) == 0)
	    {
	      ++loop;
	      var_if = malloc(sizeof(environment));
	      var_if->nom = malloc(4);
	      sprintf(var_if->nom, "%d", loop);
	      var_if->value = strdup(buffer);
	      var_if->next = NULL;
	      list->next = var_if;
	      list = var_if;
	      reading = NULL;
	    }
	  else
	    {
	      ++loop;
	      var_if = malloc(sizeof(environment));
	      var_if->nom = malloc(4);
	      sprintf(var_if->nom, "%d", loop);
	      var_if->value = strdup(buffer);
	      var_if->next = NULL;
	      list->next = var_if;
	      list = var_if;
	    }
	}
      if (strcmp(list->value, "fi") != 0)
	{
	  fprintf(stderr, "%s : Syntax error\n", buffer);
	  exit(EXIT_FAILURE);
	}
      list = list_var_if;
      list = list->next;
      str_replaced(list->value, " ", "");
      if (strcmp(list->value, "then") != 0)
	{
	  fprintf(stderr,"*%s* : Syntax error\n", list->value);
	  exit(EXIT_FAILURE);
	}
      list = list_var_if;
      list = list->next;
      list = list->next;
      int detection_else = 0;
      while (list != NULL)
	{
	  if (strcmp(list->value, "else") == 0)
	    {
	      detection_else = 1;
	    }
	  else if (strcmp(list->value, "fi") == 0)
	    {
	    }
	  else if (list->value[0] == '#')
	    {
	    }
	  else
	    {
	      if (test == 0)
		{
		  if (detection_else == 0)
		    {
		      processing_cmd(list->value, argv);
		    }
		}
	      else
		{
		  if (detection_else == 1)
		    {
		      processing_cmd(list->value, argv);
		    }
		}
	    }
	  list = list->next;
	}
    }
  else if (strncmp(buffer, "for", 3) == 0)
    {
      int loop = 0;
      environment *var_if = malloc(sizeof(environment));
      var_if->name = malloc(4);
      sprintf(var_if->name, "%d", loop);
      var_if->value = strdup(buffer);
      var_if->next = NULL;
      ++loop;
      environment *list_var_if = var_if;
      environment *list = list_var_if;
      char *reading = buffer;
      while (1)
	{
	  reading = fgets(buffer,150, file);
	  if (reading == NULL)
	    break;
	  if (buffer[strlen(buffer) - 1] == '\n')
	    buffer[strlen(buffer) - 1] = '\0';
	  processing_beginning_spaces(buffer);
	  processing_end_spaces(buffer);
	  var_if = malloc(sizeof(environment));
	  var_if->name = malloc(4);
	  sprintf(var_if->name, "%d", loop);
	  var_if->value = strdup(buffer);
	  var_if->next = NULL;
	  list->next = var_if;
	  list=var_if;
	  ++loop;
	  if (strcmp(var_if->value,"done")==0) break;
	}
      if (strcmp(list->value,"done")!=0)
	{
	  fprintf(stderr,"Syntax error: premature end of file\n");
	  exit(EXIT_FAILURE);
	}
      list=list_var_if;
      list=list->next;
      if (strcmp(list->value,"do")!=0)
	{
	  fprintf(stderr,"Syntax error: \"do\" not found in structure for\n");
	  exit(EXIT_FAILURE);
	}
      list = list_var_if;
      char *args_for[32];
      create_argument_list(args_for, list->value);
      loop = 3;
      add_environment(args_for[1], "0");
      add_environment(args_for[1], "0");
      while (args_for[loop] != NULL)
	{
	  add_environment(args_for[1], args_for[loop]);
	  list = list_var_if;
	  list = list->next;
	  list = list->next;
	  while (list != NULL)
	    {
	      if (strcmp(list->value,"done") == 0)
		break;
	      processing_cmd(list->value, argv);
	      list = list->next;
	    }
	  ++loop;
	}
    }
  else if (strcmp(buffer,"exit") == 0)
    {
      exit(EXIT_SUCCESS);
    }
  else if (strcmp(buffer, "set") == 0)
    {
      environment *list = var_environment;
      while (list != NULL)
	{
	  printf("%s=%s\n", list->name, list->value);
	  list = list->next;
	}
    }
  else if (strncmp(buffer, "unset", 5) == 0)
    {
      char *variable_name = strstr(buffer, " ");
      unsetenv(variable_name + 1);
      Environment *list = var_environment;
      Environment *previous = NULL;
      while (list != NULL)
	{
	  if (strcmp(variable_name + 1, list->name) == 0)
	    {
	      free(list->value);
	      free(list->name);
	      previous->nex = list->next;
	      free(list);
	      list =  NULL;
	    }
	  previous = list;
	  if (list != NULL)
	    list = list->next;
	}
    }
  else if (strncmp(buffer, "unset", 5) == 0)
    {
      char *variable_name = strstr(buffer," ");
      if (variable_name != NULL)
	{
	  char *variable_value = NULL;
	  Environment *list = var_environment;
	  while (list != NULL)
	    {
	      if (strcmp(variable_name + 1, list->name) == 0)
		{
		  variable_value = list->value;
		  list = NULL;
		  setenv(variable_name + 1, variable_value, 1);
		}
	      if (list != NULL)
		list = list->next;
	    }
	}
    }
  else if (strncmp(buffer, "!", 1) == 0)
    {
      if (strcmp(buffer, "!") == 0)
	{
	}
      else
	{
	  char *endptr = NULL;
	  int integer = strtol(buffer + 1, &endptr, 10);
	  if (integer == 0)
	    {
	      fprintf(stderr,"%s: element not found\n",buffer);
	    }
	  else
	    {
	      if (integer < 0)
		integer = histocount + integer;
	      if (integer > histocount - 1)
		{
		  fprintf(stderr,"%s: element not found\n",buffer);
		}
	      else
		{
		  int pos = ftell(history_file);
		  rewind(history_file);
		  char buffer_tmp[250];
		  int loop = 0;
		                       do
					 {
					   fgets(tmp_buffer, 150, history_file);
					   ++loop;
					 } while (loop != integer);
				       printf("%s\n", buffer_tmp);
				       pos = pos-strlen(buffer) - strlen("\n");
				       fseek(history_file,pos, SEEK_SET);
				       fprintf(history_file, "%s", buffer_tmp);
				       strcpy(buffer, buffer_tmp);
				       if (buffer[strlen(buffer) - 1] == '\n')
					 buffer[strlen(buffer) - 1] = '\0';
				       line_processing(argv);
		}
	    }
	}
    }
  else if (strcmp(buffer,"history") == 0 || strcmp(buffer,"history - c") == 0)
    {
      if (strcmp(buffer, "history -c") == 0)
	{
	  fclose(history_file);
	  history_file = fopen(".myshel_history", "w+");
	  historycount = 1;
	}
      else if (strcmp(buffer,"history") == 0)
	{
	  rewind(history_file);
	  char buffer_tmp[150];
	  historycount = 1;
	  char *return_reading = buffer_tmp;
	  while (!feof(history_file) || return_read == NULL)
	    {
	      char *return_reading = fgets(buffer_tmp, 150, file_history);
	      if (return_read != NULL)
		{
		  printf("%4d %s", histocount, buffer_tmp);
		  ++histocount;
		}
	    }
	}
    }
  else if (strncmp(buffer, "exit", 4) == 0)
    {
      exit(EXIT_SUCCESS);
    }
  else
    {
      char *cmd = strdup(buffer);
      char *tmp = strtok(cmd, ";");
      while (tmp != NULL)
	{
	  char *var_value = strstr(tmp, "=");
	  if (var_value != NULL)
	    {
	      char *var_name = strndup(tmp, strlen(tmp) - strlen(var_value));
	      add_environment(var_name, var_value + 1);
	      free(var_name);
	    }
	  else
	    processing_cmd(tmp, argv);
	  tmp = strtok(NULL, ";");
	}
      free(cmd);
    }
}
