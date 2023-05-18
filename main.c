#include "shell.h"
/**
* main - ...
*
*@argc: ...
*@argv: ...
*@arge: ...
*
*/

int main(int argc, char *argv[], char *arge[]);

{

  add_environment("HITSIZE", "500");
  file_history = fopen(".myshel_history", "r+");
  if (history_file == NULL)
  history_file = fopen(".myshel_history","w+");
  historycount = 1;
  char *return_read = buffer;
  while (!feof(history_file) || return_read == NULL)
    {
      char *return_reading = fgets(buffer, 150, history_file);
      if (return_read != NULL)
	{
	  ++histocount;
	}
    }
  --histocount;
  if (histocount > HISTO_SIZE)
    {
      int number_to_delete = histocount - 500;
      int loop;
      rewind(history_file);
      for (loop = 0; loop < number_to_remove; ++loop)
	{
	  fgets(buffer, 150, history_file);
	}
      FILE *file_history2 = fopen(".myshel_history_temp", "w+");
      historycount = 1;
      while (!feof(history_file) || return_read == NULL)
	{
	  char *return_reading = fgets(buffer, 150, history_file);
	  fprintf(history_file2, "%s", buffer);
	  if (return_read != NULL)
	    {
	      ++histocount;
	    }
	}
      fclose(history_file2);
      fclose(history_file);
      remove(".myshel_history");
      rename(".myshel_history_temp",".myshel_history");
      file_history = fopen(".myshel_history", "r+");
      fseek(history_file, 0, SEEK_END);
    }
  global_argc = argc;
  int increment = 0;
  while (arge[increment] != NULL)
    {
      char *value = strstr(arge[increment], "=");
      char *name = strndup(arge[increment], strlen(arge[increment]) - strlen(value));
      add_environment(name, value + 1);
      free(name);
      ++increment;
    }
  if (argc > 1)
    {
      file = fopen(argv[1], "r");
      if (file == NULL)
	{
	  fprintf(stderr, "%s: %s\n",argv[1],strerror(errno));
	  exit(EXIT_FAILURE);
	}
    }
  else
    {
      file = stdin;
    }
  while(!feof(file))
    {
      if (argc == 1)
	printf("Prompt: ");
      char *read = fgets(buffer, 150, file);
      if (read == NULL)
	{
	  exit(EXIT_SUCCESS);
	}
      if (argc == 1)
	fprintf(history_file,"%s",buffer);
      if (buffer[strlen(buffer) - 1] == '\n')
	buffer[strlen(buffer) - 1] = '\0';
      line_processing(argv);
    }
  return (0);
}