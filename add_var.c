#include "shell.h"

/**
 * *Add_Variable - Add_Variable function adds up a variable
 * at the end of a dame list.
 * @head: head.
 * @lvar: length of variable.
 * @val: value of variable.
 * @lval: len of value.
 * Return: the address of the head.
 */
dame *Add_Variable(dame **head, int lvar, char *val, int lval)
{
	dame *fresh, *x;

	fresh = malloc(sizeof(dame));
	if (fresh == NULL)
		return (NULL);

	fresh->Length_of_variable = lvar;
	fresh->val = val;
	fresh->Length_of_value = lval;

	fresh->next = NULL;
	x = *head;

	if (x == NULL)
	{
		*head = fresh;
	}
	else
	{
		while (x->next != NULL)
			x = x->next;
		x->next = fresh;
	}

	return (*head);
}

/**
 * Free_var - Free_var function frees up a dame list
 * @head: head.
 * Return: no return.
 */
void Free_var(dame **head)
{
	dame *x;
	dame *curl;

	if (head != NULL)
	{
		curl = *head;
		while ((x = curl) != NULL)
		{
			curl = curl->next;
			free(x);
		}
		*head = NULL;
	}
}

/**
 * path_err_info - path_err_info function displays the
 * error info for env in get_env.
 * @dsh: data relevant
 * Return: an error message.
 */


char *path_err_info(shell_shell *dsh)
{
	int lat;
	char *d_s;
	char *o;

	d_s = int_toString(dsh->counter);
	lat = string_length(dsh->ichi[0]) + string_length(d_s);
	lat += string_length(dsh->args[0]) + 24;
	o = malloc(sizeof(char) * (lat + 1));
	if (o == 0)
	{
		free(o);
		free(d_s);
		return (NULL);
	}
	concpy(o, dsh->ichi[0]);
	concat(o, ": ");
	concat(o, d_s);
	concat(o, ": ");
	concat(o, dsh->args[0]);
	concat(o, ": insufficient permission\n");
	concat(o, "\0");
	free(d_s);
	return (o);
}
/**
 * error_information - error_information function displays error
 * info for path and failure denied permission.
 * @dsh: data relevant.
 * Return: error string.
 */

char *error_information(shell_shell *dsh)
{
	int lat;
	char *o;
	char *d_s;
	char *message;

	d_s = int_toString(dsh->counter);
	message = ": Cannot add or Remove environment\n";
	lat = string_length(dsh->ichi[0]) + string_length(d_s);
	lat += string_length(dsh->args[0]) + string_length(message) + 4;
	o = malloc(sizeof(char) * (lat + 1));
	if (o == 0)
	{
		free(o);
		free(d_s);
		return (NULL);
	}

	concpy(o, dsh->ichi[0]);
	concat(o, ": ");
	concat(o, d_s);
	concat(o, ": ");
	concat(o, dsh->args[0]);
	concat(o, message);
	concat(o, "\0");
	free(d_s);

	return (o);
}
