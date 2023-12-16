#include "shell.h"

/**
 * _buff_comm - buff_comm function is full of buffer chained commands
 * @info: parameter structure
 * @buf: address of buff
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t buff_comm(info_t *info, char **buf, size_t *len)
{
	ssize_t s = 0;
	size_t len_q = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		s = getline(buf, &len_q, stdin);
#else
		s = _getline(info, buf, &len_q);
#endif
		if (s > 0)
		{
			if ((*buf)[s - 1] == '\n')
			{
				(*buf)[s - 1] = '\0'; /* remove trailing newline */
				s--;
			}
			info->linecount_flag = 1;
			remove_comm(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = s
				info->cmd_buf = buf;
			}
		}
	}
	return (s);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t getLine_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t j, k, length;
	ssize_t s = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	s = input_buf(info, &buf, &length);
	if (s == -1) /* EOF */
		return (-1);
	if (length)	/* we have commands left in the chain buffer */
	{
		k = j; /* init new iterator to current buf position */
		p = buf + j; /* get pointer for return */

		check_chain(info, buf, &k, j, length);
		while (k < length) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &k))
				break;
			k++;
		}

		j = k + 1; /* increment past nulled ';'' */
		if (j >= length)/* reached end of buffer? */
		{
			j = length = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (s); /* return length of buffer from _getline() */
}

/**
 * read_buffer - read_buffer function reads a buffer
 * @info: parameter structure
 * @buf: buffer
 * @i: size
 *
 * Return: s
 */
ssize_t read_buffer(info_t *info, char *buf, size_t *i)
{
	ssize_t s = 0;

	if (*i)
		return (0);
	s = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = s;
	return (s);
}

/**
 * _getNextline_Inp - _getNextline_Inp function gets the
 * next line of input from STDIN
 * @info: parameter structure
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr
 * Return: t
 */
int _getNextline_Inp(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t j, leng;
	size_t l;
	ssize_t s = 0, t = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		t = *length;
	if (j == leng)
		j = leng = 0;

	s = read_buf(info, buf, &leng);
	if (s == -1 || (s == 0 && leng == 0))
		return (-1);

	c = _strchr(buf + j, '\n');
	l = c ? 1 + (unsigned int)(c - buf) : leng;
	new_p = _realloc(p, t, t ? t + l : l + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (t)
		_strncat(new_p, buf + k, l - j);
	else
		_strncpy(new_p, buf + j, l - j + 1);

	t += l - j;
	j = l;
	p = new_p;

	if (length)
		*length = t;
	*ptr = p;
	return (t);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sig_intHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
