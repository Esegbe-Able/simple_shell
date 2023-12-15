#include "shell.h"

/**
 * str_toInt -str_toInt function converts a string to an integer
 * @s: str to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
int str_toInt(char *s)
{
	int j = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (j = 0;  s[j] != '\0'; j++)
	{
		if (s[j] >= '0' && s[j] <= '9')
		{
			result *= 10;
			result += (s[j] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_err_msg - print_err_msg function prints an error message
 * @info: the parameter
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
void print_err_msg(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_decimal - function prints a decimal (integer) number (base 10)
 * @input: input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_decimal(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j, count_it = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count_it++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + current / j);
			count_it++;
		}
		current %= j;
	}
	__putchar('0' + current);
	count_it++;

	return (count);
}

/**
 * converter_function - This converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *converter function(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sig = 0;
	char *ptr;
	unsigned long m = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		m = -num;
		sig = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		m /= base;
	} while (m != 0);

	if (sig)
		*--ptr = sig;
	return (ptr);
}

/**
 * remove_comm - remove_comm function replaces first instance of '#' with '\0'
 * @buf: address of string to be modfied
 *
 * Return: Always 0;
 */
void remove_comm(char *buf)
{
	int j;

	for (j = 0; buf[j] != '\0'; j++)
		if (buf[j] == '#' && (!j || buf[j - 1] == ' '))
		{
			buf[j] = '\0';
			break;
		}
}
