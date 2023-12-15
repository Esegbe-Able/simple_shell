#include "shell.h"

/**
 * history_list - history_list displays the history list.
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *  Return: Always 0
 */
int history_list(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * alias_toString - alias_toString function sets alias to string
 * @info: parameter structure
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_toString(info_t *info, char *str)
{
	char *p, c;
	int reti;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	reti = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (reti);
}

/**
 * set_aliasTo_string - set_aliasTo_string function sets alias to string
 * @info: parameter structure
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_aliasTo_string(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (alias_toString(info, str));

	alias_toString(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias_str - print_alias_str prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias_str(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - my_alias mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int my_alias(info_t *info)
{
	int j = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		p = _strchr(info->argv[j], '=');
		if (p)
			set_aliasTo_string(info, info->argv[j]);
		else
			print_alias_str(node_starts_with(info->alias, info->argv[j], '='));
	}

	return (0);
}
