#include "shell.h"

/**
 * list_length - list_length function  determines length of linked list
 * @h: ptr to first node
 * Return: size of list
 */
size_t list_length(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * list_toStrings - **list_toStrings function returns an
 * array of strings of the list->str
 * @head: ptr to first node
 * Return: array of strings
 */
char **list_toStrings(list_t *head)
{
	list_t *node = head;
	size_t i = list_length(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcopy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * printList_elements - printList_elements function prints
 * all elements of a list_t linked list
 * @h: ptr to first node
 * Return: size of list
 */
size_t printList_elements(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_inputs(converter_function(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_inputs(h->str ? h->str : "(nil)");
		_inputs("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * *node_with_pref - *node_with_pref function returns
 * node whose string starts with prefix
 * @node: ptr to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_with_pref(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_nodeIndex - get_nodeIndex function gets the index of a node
 * @head: ptr to list head
 * @node: ptr to the node
 *
 * Return: index of node or -1
 */
ssize_t get_nodeIndex(list_t *head, list_t *node)
{
	size_t j = 0;

	while (head)
	{
		if (head == node)
			return (j);
		head = head->next;
		j++;
	}
	return (-1);
}
