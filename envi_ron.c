#include "shell.h"

/**
 * current_env - current_env prints the current environment
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int current_env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * getenv_val - getenv_val gets the value of an environ variable
 * @info: Structure containing potential arguments.
 * @name: env variable name
 * Return: the value
 */
char *getenv_val(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * new_setenv - new_setenv function initializes a new environment variable,
 * or modify an existing one
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int new_setenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * rem_env_var - rem_env_var function remove an environment variable
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int rem_env_var(info_t *info)
{
	int j;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * pop_env_list - pop_env_list function  populates env linked list
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int pop_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_node_end(&node, environ[j], 0);
	info->env = node;
	return (0);
}
