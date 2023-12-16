#include "shell.h"

/**
 * hshh - hshh is the main shell loop
 * @info: parameter & return info structure
 * @av: argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hshh(info_t *info, char **av)
{
	ssize_t s = 0;
	int builtIn_ret = 0;

	while (s != -1 && builtIn_ret != -2)
	{
		clear_info(info);
		if (interact_iveness(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		s = getLine_input(info);
		if (s != -1)
		{
			set_info(info, av);
			builtIn_ret = find_builtin(info);
			if (builtIn_ret == -1)
				find_cmd(info);
		}
		else if (interact_iveness(info))
			_putchar('\n');
		free_info(info, 0);
	}
	create_history(info);
	free_info(info, 1);
	if (!interact_iveness(info) && info->status)
		exit(info->status);
	if (builtIn_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtIn_ret);
}

/**
 * find_built_In - find_built_In function finds a builtin command
 * @info: parameter & return info structure
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * -2 if builtin signals exit()
 */
int find_built_In(info_t *info)
{
	int j, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", exit_shell},
		{"env", current_env},
		{"help", get_help},
		{"history", history_list},
		{"setenv", new_setenv},
		{"unsetenv", rem_env_var},
		{"cd", change_mycd},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (j = 0; builtintbl[i].type; j++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[j].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmdIn_path - find_cmdIn_path function finds a command in PATH
 * @info: parameter & return info struct
 *
 * Return: void
 */
void find_cmdIn_path(info_t *info)
{
	char *path = NULL;
	int j, l

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (j = 0, l = 0; info->arg[j]; j++)
		if (!is_delim(info->arg[j], " \t\n"))
			l++;
	if (!l)
		return;

	path = find_path(info, getenv_val(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interact_iveness(info) || getenv_val(info, "PATH=")
			|| info->argv[0][0] == '/') && is_exc(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_err_msg(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - fork_cmd function forks a an exec thread to run cmd
 * @info: parameter
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ_str(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_err_msg(info, "Permission denied\n");
		}
	}
}
