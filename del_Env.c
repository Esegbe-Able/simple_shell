#include "shells.h"
/**
 * PGLA - PGLA function copies info to create
 * a fresh env or alias
 * @name: name
 * @value: value
 * Return: fresh
 */
char *PGLA(char *name, char *value)
{
	char *fresh;
	int length_name, Length_of_val, length;

	length_name = string_length(name);
	Length_of_val = string_length(value);
	length = length_name + Length_of_val + 2;
	fresh = malloc(sizeof(char) * (length));
	dup_string(fresh, name);
	concate_nate(fresh, "=");
	concate_nate(fresh, value);
	concate_nate(fresh, "\0");

	return (fresh);
}
/**
 * set_env_var - set_env_var function sets an environment variable
 * @name: name of the env var
 * @value: value of the env_var
 * @dsh: data structure
 * Return: no return
 */
void set_env_var(char *name, char *value, shells_shell *dsh)
{
	int v;
	char *var_env, *name_env;

	for (v = 0; dsh->env_variable[v]; v++)
	{
		var_env = dup_str(dsh->env_variable[v]);
		name_env = split_str(var_env, "=");
		if (comp_are(name_env, name) == 0)
		{
			free(dsh->env_variable[v]);
			dsh->env_variable[v] = PGLA(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	dsh->env_variable = ptr_malloc(dsh->env_variable, v,
			sizeof(char *) * (v + 2));
	dsh->env_variable[v] = PGLA(name, value);
	dsh->env_variable[v + 1] = NULL;
}

/**
 * comp_envVar_names - The comp_envVar_names function
 * compares env variables names with the name passed.
 * @dsh: data relevant
 * Return: 1 on success.
 */
int comp_envVar_names(shells_shell *dsh)
{

	if (dsh->args[1] == NULL || dsh->args[2] == NULL)
	{
		G_err(dsh, -1);
		return (1);
	}

	set_env_var(dsh->args[1], dsh->args[2], dsh);

	return (1);
}

/**
 * del_env_var - del_env_var function deletes a environment variable
 * @dsh: data relevant
 * Return: 1 on success.
 */
int del_env_var(shells_shell *dsh)
{
	char **reallocenv_variable;
	char *var_env, *name_env;
	int i, j, k;

	if (dsh->args[1] == NULL)
	{
		G_err(dsh, -1);
		return (1);
	}
	k = -1;
	for (i = 0; dsh->env_variable[i]; i++)
	{
		var_env = dup_str(dsh->env_variable[i]);
		name_env = split_str(var_env, "=");
		if (comp_are(name_env, dsh->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		G_err(dsh, -1);
		return (1);
	}
	reallocenv_variable = malloc(sizeof(char *) * (i));
	for (i = j = 0; dsh->env_variable[i]; i++)
	{
		if (i != k)
		{
			reallocenv_variable[j] = dsh->env_variable[i];
			j++;
		}
	}
	reallocenv_variable[j] = NULL;
	free(dsh->env_variable[k]);
	free(dsh->env_variable);
	dsh->env_variable = reallocenv_variable;
	return (1);
}
