#include "shell.h"
/**
 * free_data - f_data function frees data structure
 * @dsh: data structure
 * Return: no return
 **********************************/
void free_data(shell_shell *dsh)
{
unsigned int v = 0;
while (dsh->env_variable[v])
{
free(dsh->env_variable[v]);
v++;
}

free(dsh->env_variable);
free(dsh->process_id);
}

/**
 * set_data - set_data function nitialize data struct
 * @dsh: data structure
 * @ichi: arg vector
 * Return: no return
 **********************************/
void set_data(shell_shell *dsh, char **ichi)
{
	unsigned int v = 0;

	dsh->ichi = ichi;
	dsh->input = NULL;
	dsh->args = NULL;
	dsh->status = 0;
	dsh->counter = 1;

	for (v = 0; environ[v]; v++)
		;

	dsh->env_variable = malloc(sizeof(char *) * (v + 1));

	for (v = 0; environ[v]; v++)
	{
		dsh->env_variable[v] = dup_str(environ[v]);
	}

	dsh->env_variable[v] = NULL;
	dsh->process_id = int_toString(getpid());
}



/**
 * main - Main entry point
 * @ac: argument count
 * @ichi: argument vector
 * Return: 0 on success.
 */
int main(int ac, char **ichi)
{
	shell_shell dsh;
	(void) ac;

	signal(SIGINT, sing_line);
	set_data(&dsh, ichi);
	loop_shell(&dsh);
	free_data(&dsh);
	if (dsh.status < 0)
		return (255);
	return (dsh.status);
}
