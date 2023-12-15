#include "shells.h"

/**
 * help_ - Help is the entry point for help info for help builtin
 * Return: no return
 */
void help_(void)
{
	char *help = "$ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, string_length(help));
	help = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, help, string_length(help));
	help = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, help, string_length(help));
	help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help, string_length(help));
	help = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, help, string_length(help));
	help = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, help, string_length(help));
	help = "unsetenv [variable]\n";
	write(STDOUT_FILENO, help, string_length(help));
}


/**
 * h_env_setup - h_env_setup help info for builtin setenv
 * Return: no return
 */
void h_env_setup(void)
{
	char *help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help, string_length(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, string_length(help));
	help = "Add a new path or directory to the environment\n";
	write(STDOUT_FILENO, help, string_length(help));
}
/**
 * h_env_info_env - h_env_info_env function is the help info for builtin env
 * Return: no return
 */
void h_env_info_env(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, string_length(help));
	help = "Print the environment of the shell.\n";
	write(STDOUT_FILENO, help, string_length(help));
}


/**
 * exit_builtin - exit_builtin function help info for builtin exit
 * Return: no return
 */
void exit_builtin(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, help, string_length(help));
	help = "Exits the shell with a status of N. If N is omitted, the exit";
	write(STDOUT_FILENO, help, string_length(help));
	help = "status is that of the last command executed\n";
	write(STDOUT_FILENO, help, string_length(help));
}


/**
 * h_env_unsetenv - h_env_unsetenv function Help info for builtin unsetenv
 * Return: no return
 */
void h_env_unsetenv(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help, string_length(help));
	help = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, help, string_length(help));
}
