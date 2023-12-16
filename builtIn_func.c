#include "shell.h"

/**
 * exit_shell - This function's work is to exit the shell
 * @info: Structure containing potential arguments.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int exit_shell(info_t *info)
{
	int exit_check;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exit_check = str_toInt(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			print_err_msg(info, "Illegal number: ");
			print_InpStr(info->argv[1]);
			write_char('\n');
			return (1);
		}
		info->err_num = str_toInt(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * change _mycd - change_mycd changes the current directory of the process
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int change_mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int changedir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_inputs("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = getenv_val(info, "HOME=");
		if (!dir)
			changedir_ret = /* TODO: what should this be? */
				chdir((dir = getenv_val(info, "PWD=")) ? dir : "/");
		else
			changedir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!getenv_val(info, "OLDPWD="))
		{
			_inputs(s);
			_putchar('\n');
			return (1);
		}
		_inputs(getenv_val(info, "OLDPWD=")), _putchar('\n');
		changedir_ret = /* TODO: what should this be? */
			chdir((dir = getenv_val(info, "OLDPWD=")) ? dir : "/");
	}
	else
		changedir_ret = chdir(info->argv[1]);
	if (changedir_ret == -1)
	{
		print_err_msg(info, "can't cd to ");
		print_InpStr(info->argv[1]), write_char('\n');
	}
	else
	{
		_set_env_Var(info, "OLDPWD", getenv_val(info, "PWD="));
		_set_env_Var(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * get_help - get_help functions finds you help
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int get_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_inputs("help call works. Function not yet implemented \n");
	if (0)
		_inputs(*arg_array); /* temp att_unused workaround */
	return (0);
}
