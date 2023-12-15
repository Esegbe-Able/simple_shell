#include "shells.h"
/**
 * dir_check - dir_check function checks ":" if is in
 * the current directory.
 * @path: character pointer.
 * @m: int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int dir_check(char *path, int *m)
{
	if (path[*m] == ':')
		return (1);

	while (path[*m] != ':' && path[*m])
	{
		*m += 1;
	}

	if (path[*m])
		*m += 1;

	return (0);
}
/**
 * locate_com - locate_com function locates a command
 * @cmd: name of the command
 * @env_variable: env variable
 * Return: location of the command.
 */
char *locate_com(char *cmd, char **env_variable)
{
	char *path, *ptr_path, *token_path, *d;
	int length_dir, length_cmd, v;
	struct stat st;

	path = obtain_env_var("PATH", env_variable);
	if (path)
	{
		ptr_path = dup_str(path);
		length_cmd = string_length(cmd);
		token_path = split_str(ptr_path, ":");
		v = 0;
		while (token_path != NULL)
		{
			if (dir_check(path, &v))
				if (stat(cmd, &st) == 0)
					return (cmd);
			length_dir = string_length(token_path);
			d = malloc(length_dir + length_cmd + 2);
			dup_string(d, token_path);
			concate_nate(d, "/");
			concate_nate(d, cmd);
			concate_nate(d, "\0");
			if (stat(d, &st) == 0)
			{
				free(ptr_path);
				return (d);
			}
			free(d);
			token_path = split_str(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}
/**
 * execute_check - execute_check function checks if is an executablev file
 * @dsh: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int execute_check(shells_shell *dsh)
{
	struct stat st;
	int v;
	char *input;

	input = dsh->args[0];
	for (v = 0; input[v]; v++)
	{
		if (input[v] == '.')
		{
			if (input[v + 1] == '.')
				return (0);
			if (input[v + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[v] == '/' && v != 0)
		{
			if (input[v + 1] == '.')
				continue;
			v++;
			break;
		}
		else
			break;
	}
	if (v == 0)
		return (0);

	if (stat(input + v, &st) == 0)
	{
		return (v);
	}
	G_err(dsh, 127);
	return (-1);
}
/**
 * user_perm - user_perm function is meant to verify if
 * user has permissions to access
 * @d: destination
 * @dsh: data structure
 * Return: 1 if there is an error, 0 if not
 */
int user_perm(char *d, shells_shell *dsh)
{
	if (d == NULL)
	{
		G_err(dsh, 127);
		return (1);
	}

	if (comp_are(dsh->args[0], d) != 0)
	{
		if (access(d, X_OK) == -1)
		{
			G_err(dsh, 126);
			free(d);
			return (1);
		}
		free(d);
	}
	else
	{
		if (access(dsh->args[0], X_OK) == -1)
		{
			G_err(dsh, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * execute_cmd - execute_cmd function executes command lines
 * @dsh: relevant data
 * Return: 1 on success.
 */
int execute_cmd(shells_shell *dsh)
{
	pid_t pd;
	pid_t wpd;
	int stat;
	int execut;
	char *d;
	(void) wpd;

	execut = execute_check(dsh);
	if (execut == -1)
		return (1);
	if (execut == 0)
	{
		d = locate_com(dsh->args[0], dsh->env_variable);
		if (user_perm(d, dsh) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (execut == 0)
			d = locate_com(dsh->args[0], dsh->env_variable);
		else
			d = dsh->args[0];
		execve(d + execut, dsh->args, dsh->env_variable);
	}
	else if (pd < 0)
	{
		perror(dsh->ichi[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &stat, WUNTRACED);
		} while (!WIFEXITED(stat) && !WIFSIGNALED(stat));
	}

	dsh->status = stat / 256;
	return (1);
}
