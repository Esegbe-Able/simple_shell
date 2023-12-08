#include "shell.h"
/**
 * ass_line - ass_line function is meant to assign the
 * line var for get_line
 * @lptr: Storage buffer
 * @buffer: string that is been called to line
 * @i: the size of line
 * @k: size of the buffer
 */
void ass_line(char **lptr, size_t *i, char *buffer, size_t k)
{

	if (*lptr == NULL)
	{
		if  (k > BUFSIZE)
			*i = k;

		else
			*i = BUFSIZE;
		*lptr = buffer;
	}
	else if (*i < k)
	{
		if (k > BUFSIZE)
			*i = k;
		else
			*i = BUFSIZE;
		*lptr = buffer;
	}
	else
	{
		concpy(*lptr, buffer);
		free(buffer);
	}
}
/**
 * Change_Dir - The function changes the current directory
 * @dsh: data relevant
 * Return: 1 on success
 */
int Change_Dir(shell_shell *dsh)
{
	char *d;
	int id, i3, ig;

	d = dsh->args[1];

	if (d != NULL)
	{
		id = concomp("$HOME", d);
		i3 = concomp("~", d);
		ig = concomp("--", d);
	}

	if (d == NULL || !id || !i3 || !ig)
	{
		changeDir_(dsh);
		return (1);
	}

	if (concomp("-", d) == 0)
	{
		changeDir_prev(dsh);
		return (1);
	}

	if (concomp(".", d) == 0 || concomp("..", d) == 0)
	{
		Change_Dir(dsh);
		return (1);
	}

	Change_Dir(dsh);

	return (1);
}


/**
 * read_input - read_input function reads inptu from stream
 * @lptr: buffer
 * @i: size of line pointer
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t read_input(char **lptr, size_t *i, FILE *stream)
{
	int m;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char u = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (u != '\n')
	{
		m = read(STDIN_FILENO, &u, 1);
		if (m == -1 || (m == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (m == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = prrealloc(buffer, input, input + 1);
		buffer[input] = u;
		input++;
	}
	buffer[input] = '\0';
	theLIne(lptr, i, buffer, input);
	retval = input;
	if (m != 0)
		input = 0;
	return (retval);
}



/**
 * exit_shell - exit_shell function exit the shell
 * @dsh: data
 * Return: 0 on success.
 */
int exit_shell(shell_shell *dsh)
{
	unsigned int i;
	int jiggy;
	int sterling;
	int big_num;

	if (dsh->args[1] != NULL)
	{
		i = string_toInt(dsh->args[1]);
		jiggy = check_if_int(dsh->args[1]);
		sterling = Length_ofString(dsh->args[1]);
		big_num = i > (unsigned int)INT_MAX;
		if (!jiggy || sterling > 10 || big_num)
		{
			G_ERROR(dsh, 2);
			dsh->status = 2;
			return (1);
		}
		dsh->status = (i % 256);
	}
	return (0);

}
