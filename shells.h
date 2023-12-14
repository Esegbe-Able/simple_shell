#ifndef _shells_h_
#define _shells_h_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <string.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

extern char **environ;

/*struct data - struecure*/
typedef struct data
{
	char **ichi;
	char *input;
	char **args;
	int status;
	int counter;
	char **env_variable;
	char *process_id;
} shells_shell;

typedef struct def_s
{
	char separator;
	struct def_s *next;
} def;

typedef struct dap_s
{
	char *line;
	struct dap_s *next;
} dap;

typedef struct dame_list
{
	int Length_of_variable;
	char *val;
	int Length_of_value;
	struct dame_list *next;
} dame;

typedef struct builtin_s
{
	char *name;
	int (*f)(shells_shell *dsh);
} builtin_t;

char *big_ups(shells_shell *dsh, char *message, char *o, char *d_s);
char *errorMessage_cd(shells_shell *dsh);
char *generic_messages(shells_shell *dsh);
char *exit_get(shells_shell *dsh);

char *dup_str(const char *s);
int string_length(const char *s);
int compChar_str(char string[], const char *delim);
char *split_str(char string[], const char *delim);
int check_ifInt(const char *s);

void Rev_string(char *s);

void Change_Directory(shells_shell *dsh);
void ChangeUser_dir(shells_shell *dsh);
void changeprev_dir(shells_shell *dsh);
void change_dir(shells_shell *dsh);

int Change_Dir(shells_shell *dsh);

int countChar_rep(char *input, int u);
int syntax_error(char *input, int u, char last);
int char_index(char *input, int *u);
void err_message(shells_shell *dsh, char *input, int u, int bool);
int caseint_function(shells_shell *dsh, char *input);

int builtIn_com(shells_shell *dsh);

int exit_shell(shells_shell *dsh);

int (*builtINFunctions(char *cmd))(shells_shell *);

int G_err(shells_shell *dsh, int eva);

int HELP(shells_shell *dsh);

void ass_line(char **lptr, size_t *i, char *buffer, size_t k);
ssize_t read_input(char **lptr, size_t *i, FILE *stream);

void ctrl_prompt(int sig);
char *readInp_str(int *dub);

char *del_com(char *in);
void loop_shell(shells_shell *dsh);

char *non_printed_char_swap(char *input, int bool);
void addSeparators_cdLists(def **hs, dap **hl, char *input);
void next_In_Line(def **l_s, dap **l_l, shells_shell *dsh);
int split(shells_shell *dsh, char *input);
char **splityy(char *input);

void h_env_info_env(void);
void h_env_setup(void);
void h_env_unsetenv(void);
void help_(void);
void exit_builtin(void);

void help_option(void);
void a_help_option(void);
void builtIn_help(void);

def *add_node(def **top, char sep);
void freee_list(def **top);
dap *end_node(dap **top, char *line);
void freelist(dap **top);

dame *Add_Variable(dame **head, int lvar, char *val, int lval);
void Free_var(dame **head);

void copy_info(void *newptr, const void *ptr, unsigned int size);
void *realloc_mem(void *ptr, unsigned int old_size, unsigned int new_size);
char **ptr_malloc(char **ptr, unsigned int old_size, unsigned int new_size);

int getlength_Int(int n);
char *int_to_string(int n);
int stringto_int(char *s);

char *concate_nate(char *dest, const char *src);
char *dup_string(char *dest, char *src);
int comp_are(char *s1, char *s2);
char *string_locate(char *s, char c);
int take_string(char *s, char *rec);

void right_variable(dame **h, char *in, shells_shell *data);
int plenty_money(dame **h, char *in, char *st, shells_shell *data);
char *rep_string(dame **head, char *input, char *new_input, int nlen);
char *replace_var(char *input, shells_shell *dsh);

char *PGLA(char *name, char *value);
void set_env_var(char *name, char *value, shells_shell *dsh);
int comp_envVar_names(shells_shell *dsh);
int del_env_var(shells_shell *dsh);

int comp_env_names(const char *nenv, const char *name);
char *obtain_env_var(const char *name, char **env_variable);
int print_env_var(shells_shell *dsh);

int dir_check(char *path, int *m);
char *locate_com(char *cmd, char **env_variable);
int execute_check(shells_shell *dsh);
int user_perm(char *d, shells_shell *dsh);
int exec_cmd(shells_shell *dsh);

char *error_information(shells_shell *dsh);
char *path_err_info(shells_shell *dsh);

void free_data(shells_shell *dsh);
void set_data(shells_shell *dsh, char **ichi);

#endif
