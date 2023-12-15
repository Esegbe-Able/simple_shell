#include "shell.h"

/**
 * interact_iveness - interact_iveness function returns true
 * if shell is interactive mode
 * @info: structure address
 * Return: 1 if interactive mode, 0 otherwise
 */
int interact_iveness(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * check_delim - check_delim function checks if character is a delimeter
 * @c: character to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int check_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * check_isalpha - check_isalpha function checks for alphabetic character
 * @c: character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int check_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_btio - _btio function converts a string to an integer
 *@s: string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _btio(char *s)
{
	int j, sig = 1, flag = 0, output;
	unsigned int result = 0;

	for (j = 0;  s[j] != '\0' && flag != 2; j++)
	{
		if (s[j] == '-')
			sig *= -1;

		if (s[j] >= '0' && s[j] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[j] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sig == -1)
		output = -result;
	else
		output = result;

	return (output);
}
