#include "shell.h"

/**
 *
 * processing_cmd - ..
 *
 *@cmd: ...
 *@argv: ...
 *
 */

void processing_cmd(char *cmd, char **argv)
{

char *cmd1,*cmd2;
char *outgoing_redirection_file, *incoming_redirection_file;
char *outgoing_redirection_file2, *incoming_redirection_file2;
int pipefd[2];

cmd2 = NULL;
str_replaced(cmd, "\n", "");
str_replaced(cmd, " <", "<");
str_replaced(cmd, "< ", "<");
str_replaced(cmd, "<", " < ");
str_replaced(cmd, " >", ">");
str_replaced(cmd, "> ", ">");
str_replaced(cmd, ">", " > ");
str_replaced(cmd, " >  > ", " >> ");
str_replaced(cmd,"| ", "|");
str_replaced(cmd," |", "|");
str_replaced(cmd, "|", " | ");
char *tmp = strstr(cmd, " | ");
if (tmp != NULL)
  {
    cmd1 = strndup(cmd, strlen(cmd) - strlen(tmp));
    cmd2 = strdup(tmp +3);
  }
 else
   {
     cmd1 = strdup(cmd);
   }
create_argument_list(arg_list, cmd1);
variable_management(arg_list, argv);
joker_processing(arg_list);
outgoing_redirection_file = scan_redirection_outgoing(arg_list);
incoming_redirection_file = scan_incoming_redirection(arg_list);
if (cmd2 != NULL)
  {
    create_argument_list(arg_list2, cmd2);
    variable_management(arg_list2, argv);
    joker_processing(arg_list2);
    outgoing_redirection_file2 = scan_redirection_outgoing(arg_list2);
    incoming_redirection_file2 = scan_incoming_redirection(arg_list2);
  }
pipe(pipefd);
pid_t process = fork();
if (process == 0)
  {
    if (cmd2 != NULL)
      {
	dup2(pipefd[1], STDOUT_FILENO);
      }
    if (incoming_redirection_file != NULL)
      {
	int handler = int freopen(incoming_redirection_file, "r", stdin);
	if (handler == -1)
	  {
	    fprintf(stderr, "%s\n", strerror(errno));
	    exit(0);
	  }
      }
    if (outgoing_redirection_file != NULL)
      {
	char* redirect_type = strndup(outgoing_redirection_file, 1);
	int handler = int freopen(outgoing_redirection_file + 1, redirect_type, stdout);
	if (handler == -1)
	  {
	    fprintf(stderr, "%s\n", strerror(errno));
	    exit(0);
	  }
	free(redirect_type);
      }
    int returne = execvp(arg_list[0], arg_list);
    if (returne == -1)
      fprintf(stderr, "%s\n", strerror(errno));
    exit(0);
  }
 else
   {
     wait(&process);
   }
if (cmd2 != NULL)
  {
    pid_t process2 = fork();
    if (process2 == 0)
      {
	dup2(pipefd[0], STDIN_FILENO);
	if (incoming_redirection_file2 != NULL)
	  {
	    int handler = int freopen(incoming_redirection_file2, "r", stdin);
	    if (handler == -1)
	      {
		fprintf(stderr, "%s\n", strerror(errno));
		exit(0);
	      }
	  }
	if (outgoing_redirection_file2 != NULL)
	  {
	    char* redirect_type = strndup(outgoing_redirection_file, 1);
	    int handler = int freopen(outgoing_redirection_file2 + 1, redirect_type, stdout);
	    if (handler == -1)
	      {
		fprintf(stderr, "%s\n",strerror(errno));
		exit(0);
	      }
	    free(redirect_type);
	  }
	int returne = execvp(arg_list2[0], arg_list2);
	if (returne == -1)
	  fprintf(stderr, "%s\n", strerror(errno));
	exit(0);
      }
    else
      {
	wait(&process2);
      }
  }

if (cmd2 != NULL)
  {
    if (outgoing_redirection_file2 != NULL)
      free(outgoing_redirection_file2);
    if (incoming_redirection_file2 != NULL)
      free(incoming_redirection_file2);
    release_arg(arg_list2);
    free(cmd2);
    cmd2 = NULL;
  }
if (incoming_redirection_file != NULL)
  free(incoming_redirection_file);
if (outgoing_redirection_file != NULL)
  free(outgoing_redirection_file);
release_arg(arg_list);
free(cmd1);
}
