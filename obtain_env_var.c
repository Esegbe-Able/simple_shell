#include "shell.h"

/**
 * print_env_var - this function prints the evironment variables
 * @dsh: data relevant.
 * Return: 1 on success.
 */
int print_env_var(shell_shell *dsh)
{
	int h, i;

	for (h = 0; dsh->env_variable[h]; h++)
	{

		for (i = 0; dsh->env_variable[h][i]; i++)
			;

		write(STDOUT_FILENO, dsh->env_variable[h], i);
		write(STDOUT_FILENO, "\n", 1);
	}
	dsh->status = 0;

	return (1);
}

/**
 * comp_env_names - comp_env_names function compares env variables names
 * with the name passed.
 * @nenv: name of the env var
 * @name: name passed
 * Return: 0 if are not equal. Another value if they are.
 */
int comp_env_names(const char *nenv, const char *name)
{
	int n;

	for (n = 0; nenv[n] != '='; n++)
	{
		if (nenv[n] != name[n])
		{
			return (0);
		}
	}

	return (n + 1);
}
/**
 * obtain_en_var - obtain_en_var function get an environment variable
 * @name: name of the env_var
 * @env_variable: env var
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *obtain_env_var(const char *name, char **env_variable)
{
	char *ptr_env;
	int m, nov;

	ptr_env = NULL;
	nov = 0;

	for (m = 0; env_variable[m]; m++)
	{
		nov = compare_envnames(env_variable[m], name);
		if (nov)
		{
			ptr_env = env_variable[m];
			break;
		}
	}

	return (ptr_env + nov);
}


/**
 * check_ifInt - This function defines if string passed is a number
 * @s: input
 * Return: 1 if string is a number. 0 in other case.
 */
int check_ifInt(const char *s)
{
	unsigned int v;

	v = 0;
	while (s[v])
	{
		if (s[v] < 48 || s[v] > 57)
			return (0);
		v++;
	}
	hreturn (1);
}

/**
 * Rev_string - Rev_string function reverses a string.
 * @s: input string.
 * Return: no return.
 */
void Rev_string(char *s)
{
	int count = 0, b, c;
	char *string, y;

	for (count = 0; s[count] != '\0'; count++)
	{
		string = s;
	}

	b = 0;
	while (b < count - 1)
	{
		a = b + 1;
		while (c > 0)
		{
			y = *(string + c);
			*(string + c) = *(string + (c - 1));
			*(string + (c - 1)) = y;
			c--;
		}
		b++;
	}
}
