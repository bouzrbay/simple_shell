#ifndef SHELL_H
#define SHELL_H


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <glob.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>

#define SIZE_HISTO 500

typedef struct environment
{
  char *name;
  char *value;
  struct environment *next;
} environment;

environment *var_environment = NULL;

/**********variable declaration***********/

char *arg_list[32],*arg_list2[32];
char buffer[250];
int global_argc, histocount;
FILE *file, *file_history;


/**********OUR FUNCTIONS****************/

void add_environment(char *name_variable, char *value_variable);
void str_replaced(char *chain, char* research, char *replaced);
void create_argument_list(char *arg[], char *cmd);
void variable_management(char* arg[], char **argv);
void joker_processing(char *arg[]);
void release_arg(char *arg[]);
char *scan_incoming_redirection(char *arg[]);
char *scan_redirection_outgoing(char *arg[]);
void processing_cmd(char *cmd, char **argv);
void processing_beginning_spaces(char *string_to_process);
void line_processing(char **argv);
int main(int argc, char *argv[], char *arge[]);



#endif
