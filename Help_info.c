#include "shell.h"

/**
 * builtIn_help - builtIn_help Help info for builtin help.
 * Return: no return
 */
void builtIn_help(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, string_length(help));
	help = "\tChange the working directory.\n ";
	write(STDOUT_FILENO, help, string_length(help));
}

/**
 * help_option - help_option function is the option for help function
 * Return: no return
*/

void help_option(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, string_length(help));
	help = "\tDisplay information about commands.\n ";
	write(STDOUT_FILENO, help, string_length(help));
	help = "Display brief summary of builtin commands.\n";
	write(STDOUT_FILENO, help, string_length(help));
}

/**
 * a_help_option - same thing
 * Return: no reurn
*/

void a_help_option(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, string_length(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, string_length(help));
}


/**
 * HELP - HELP function that retrieves help messages according builtin
 * @dsh: data structure (args and input)
 * Return: Return 0
*/
int HELP(shell_shell *dsh)
{

	if (dsh->args[1] == 0)
		gen_h();
	else if (concomp(dsh->args[1], "setenv") == 0)
		h_env_setup();
	else if (concomp(dsh->args[1], "env") == 0)
		h_env_info_env();
	else if (concomp(dsh->args[1], "unsetenv") == 0)
		h_env_unsetenv();
	else if (concomp(dsh->args[1], "help") == 0)
		help_option();
	else if (concomp(dsh->args[1], "exit") == 0)
		exit_builtin();
	else if (concomp(dsh->args[1], "cd") == 0)
		builtIn_help();
	else if (concomp(dsh->args[1], "alias") == 0)
		a_help_option();
	else
		write(STDERR_FILENO, dsh->args[0],
		      string_length(dsh->args[0]));

	dsh->status = 0;
	return (1);
}
