#include "shell.h"
/**
 * right_variable - right_variable function checks if the
 * typed variable is an env variable
 * @h: head
 * @in: input string
 * @data: data struct
 * Return: no return
 */
void right_variable(dame **h, char *in, shell_shell *data)
{
	int rows, chr, l, value;
	char **_envr;

	_envr = data->env_variable;
	for (rows = 0; _envr[row]; rows++)
	{
		for (l = 1, chr = 0; _envr[rows][chr]; chr++)
		{
			if (_envr[rows][chr] == '=')
			{
				lvalue = Length_ofString(_envr[rows] + chr + 1);
				AddVariable(h, l, _envr[rows] + chr + 1, lvalue);
				return;
			}

			if (in[l] == _envr[rows][chr])
				l++;
			else
				break;
		}
	}

	for (l = 0; in[l]; l++)
	{
		if (in[l] == ' ' || in[l] == '\t' || in[l] == ';' || in[l] == '\n')
			break;
	}

	AddVariable(h, l, NULL, 0);
}
/**
 * plenty_money - function checks if the typed variable is $$ or $?
 * @h: head
 * @in: input string
 * @st: last status of the Shell
 * @data: data struct
 * Return: no return
 */
int plenty_money(dame **h, char *in, char *st, shell_shell *data)
{
	int i, first, lpd;

	first = Length_ofString(st);
	lpd = Length_ofString(data->process_id);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				AddVariable(h, 2, st, first), i++;
			else if (in[x + 1] == '$')
				AddVariable(h, 2, data->process_id, lpd), i++;
			else if (in[x + 1] == '\n')
				AddVariable(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				AddVariable(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				AddVariable(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				AddVariable(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				AddVariable(h, 0, NULL, 0);
			else
				right_var(h, in + i, data);
		}
	}

	return (i);
}

/**
 * rep_string - rep_string function replaces string with variables
 * @head: head of the linked list
 * @input: input string
 * @new_input: new input string (replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *rep_string(dame **head, char *input, char *new_input, int nlen)
{
	dame *indx;
	int i, j, y;

	indx = *head;
	i = j = 0;
	while (j < nlen)
	{
		if (input[j] == '$')
		{
			if (!(indx->Length_of_variable) && !(indx->Length_of_value))
			{
				new_input[x] = input[j];
				j++;
			}
			else if (indx->Length_of_variable && !(indx->Length_of_value))
			{
				for (y = 0; y < indx->Length_of_variable; y++)
					j++;
				i--;
			}
			else
			{
				for (y = 0; y < indx->Length_of_value; y++)
				{
					new_input[i] = indx->val[z];
					i++;
				}
				j += (indx->Length_of_variable);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}
/**
 * replace_var - replace_var function calls functions to
 * replace string into vars
 * @input: input
 * @dsh: data struct
 * Return: replaced string
 */
char *replace_var(char *input, shell_shell *dsh)
{
	dame *head, *indx;
	char *status, *new_input;
	int oldlen, newlen;

	status = int_toString(dsh->status);
	head = NULL;

	oldlen = plenty_money(&head, input, status, dsh);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	newlen = 0;

	while (indx != NULL)
	{
		newlen += (indx->Length_of_value - indx->Length_of_variable);
		indx = indx->next;
	}

	newlen += oldlen;

	new_input = malloc(sizeof(char) * (newlen + 1));
	new_input[newlen] = '\0';

	new_input = rep_string(&head, input, new_input, nlen);

	free(input);
	free(status);
	FreeVariable(&head);

	return (new_input);
}
