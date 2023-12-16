#include "shell.h"

/**
 * *get_myhistoryFile - *get_myhistoryFile pointer function
 * gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_myhistoryFile(info_t *info)
{
	char *buf, *dir;

	dir = _getehnv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * create_history - create_history function creates a file,
 * or appends to an existing file
 * @info: parameter structure
 *
 * Return: 1 on success, else -1
 */
int create_history(info_t *info)
{
	ssize_t gd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	gd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (gd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, gd);
		_putfd('\n', gd);
	}
	_putfd(BUF_FLUSH, gd);
	close(gd);
	return (1);
}

/**
 * read_hist - read_hist function reads history from file
 * @info: parameter structure
 * Return: histcount on success, 0 otherwise
 */
int read_hist(info_t *info)
{
	int j, las = 0, LineCount = 0;
	ssize_t gd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	gd = open(filename, O_RDONLY);
	free(filename);
	if (gd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(gd);
	for (j = 0; j < fsize; j++)
		if (buf[j] == '\n')
		{
			buf[j] = 0;
			build_history_list(info, buf + las, LineCount++);
			las = j + 1;
		}
	if (las != j)
		build_history_list(info, buf + las, LineCount++);
	free(buf);
	info->histcount = LineCount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_hist_list - build_hist_list function adds entry
 * to a history linked list
 * @info: Structure containing potential arguments.
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_hist_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_hist_list - renumber_hist_list renumbers the
 * history linked list after changes
 * @info: Structure containing potential arguments.
 * Return: the new histcount
 */
int renumber_hist_list(info_t *info)
{
	list_t *node = info->history;
	int j = 0;

	while (node)
	{
		node->num = j++;
		node = node->next;
	}
	return (info->histcount = j);
}
