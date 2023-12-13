#include "shell.h"

/**
 * builtINFunctions - builtin that passes the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*builtINFunctions(char *cmd))(shell_shell *)
{
	builtin_t builtIN[] = {
		{ "env", print_env },
		{ "exit", exit_shell },
		{ "setenv", comp_envVar_names },
		{ "unsetenv", del_env_var },
		{ "cd", Change_Dir },
		{ "help", HELP },
		{ NULL, NULL }
	};
	int v;

	for (v = 0; builtIN[v].name; v++)
	{
		while (concomp(builtIN[v].name, cmd) == 0)
			break;
	}

	return (builtIN[v].f);
}


/**
 * string_toInt - This function is capable of making
 * changes a string to an integer.
 * @s: the input string.
 * Return: an integer.
 */
int string_toInt(char *s)
{
	unsigned int total = 0, size = 0, oi = 0, pn = 1, m = 1, r;

	while (*(s + total) != '\0')
	{
		if (size > 0 && (*(s + total) < '0' || *(s + total) > '9'))
			break;

		if (*(s + total) == '-')
			pn *= -1;

		if ((*(s + total) >= '0') && (*(s + total) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		total++;
	}

	for (r = total - size; r < total; r++)
	{
		oi = oi + ((*(s + r) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}


/**
 *getInt_length - This function is meant to
 Get the lenght of the number.
 * @n: the type int number.
 * Return: the lenght of the number.
 */
int getInt_length(int n)
{
	unsigned int y;
	int z = 1;

	if (n < 0)
	{
		x++;
		y = n * -1;
	}
	else
	{
		x = n;
	}
	while (x > 9)
	{
		y++;
		x = x / 10;
	}

	return (y);
}

/**
 * int_toString - function changes int to string.
 * @n: the type int number
 * Return: a String.
 */
char *int_toString(int n)
{
	unsigned int x;
	int y = getInt_length(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (y + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + y) = '\0';

	if (n < 0)
	{
		x = n * -1;
		buffer[0] = '-';
	}
	else
	{
		x = n;
	}

	y--;
	do {
		*(buffer + y) = (x % 10) + '0';
		x = x / 10;
		y--;
	}
	while (x > 0)
		;
	return (buffer);
}

/**
 * case_intfunc - intermediate function to
 * find and print a syntax error
 * @dsh: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int case_intfunc(ichigos_shell *dsh, char *input)
{
	int b = 0;
	int f_char = 0;
	int i = 0;

	f_char = index_char(input, &b);
	if (f_char == -1)
	{
		error_message(dsh, input, b, 0);
		return (1);
	}

	i = syntax_err(input + b, 0, *(input + b));
	if (i != 0)
	{
		error_message(dsh, input, b + i, 1);
		return (1);
	}

	return (0);
}
