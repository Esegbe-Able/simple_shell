#include "shells.h"

/**
 * builtINFunctions - builtin that passes the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*builtINFunctions(char *cmd))(shells_shell *)
{
	builtin_t builtIN[] = {
		{ "env", print_env_var },
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
		while (comp_are(builtIN[v].name, cmd) == 0)
			break;
	}

	return (builtIN[v].f);
}


/**
 * stringto_int - This function is capable of making
 * changes a string to an integer.
 * @s: the input string.
 * Return: an integer.
 */
int stringto_int(char *s)
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
 * getlength_Int - This function is meant to
 * Get the lenght of the number.
 * @n: the type int number.
 * Return: the lenght of the number.
 */
int getlength_Int(int n)
{
	unsigned int y;
	int z = 1;

	if (n < 0)
	{
		z++;
		y = n * -1;
	}
	else
	{
		y = n;
	}
	while (y > 9)
	{
		z++;
		y = y / 10;
	}

	return (z);
}

/**
 * int_to_string - This function changes int to string.
 * @n: the type int
 * Return: a String.
 */
char *int_to_string(int n)
{
	unsigned int y;
	int z = getlength_Int(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (z + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + z) = '\0';

	if (n < 0)
	{
		y = n * -1;
		buffer[0] = '-';
	}
	else
	{
		y = n;
	}

	z--;
	do {
		*(buffer + z) = (y % 10) + '0';
		y = y / 10;
		z--;
	}
	while (y > 0)
		;
	return (buffer);
}

/**
 * caseint_function - caseint_function  intermediate function to
 * find and print a syntax error
 * @dsh: data struct
 * @input: input (string)
 * Return: 1 if there is an error. 0 in other case
 */
int caseint_function(shells_shell *dsh, char *input)
{
	int c = 0;
	int f_char = 0;
	int j = 0;

	f_char = char_index(input, &c);
	if (f_char == -1)
	{
		err_message(dsh, input, c, 0);
		return (1);
	}

	j = syntax_error(input + c, 0, *(input + c));
	if (j != 0)
	{
		err_message(dsh, input, c + j, 1);
		return (1);
	}

	return (0);
}
