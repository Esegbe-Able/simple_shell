#include "shell.h"

/**
 * non_printed_char_swap - swaps | and & for non-printed chars
 * @input: input
 * @bool: swap
 * Return: swapped string
 */
char *non_printed_char_swap(char *input, int bool)
{
	int v;

	if (bool == 0)
	{
		v = 0;
		while (input[v])
		{
			if (input[v] == '|')
			{
				if (input[v + 1] != '|')
					input[v] = 16;
				else
					v++;
			}
			if (input[v] == '&')
			{
				if (input[v + 1] != '&')
					input[v] = 12;
				else
					v++;
			}
			v++;
		}
	}
	else
	{
		v = 0;
		while (input[v])
		{
			input[v] = (input[v] == 16 ? '|' : input[v]);
			input[v] = (input[v] == 12 ? '&' : input[v]);
			v++;
		}
	}
	return (input);
}
/**
 * addSeparators_&_cdLists -This function ie meant to add
 * separators and command lines in the lists
 * @hs: head
 * @hl: head of command lines list
 * @input: input(in string)
 * Return: no return
 */
void addSeparators_&_cdLists(def **hs, dap **hl, char *input)
{
	int v;
	char *line;

	input = non_printed_char_swap(input, 0);

	for (v = 0; input[v]; v++)
	{
		if (input[v] == ';')
			add_node(hs, input[v]);

		if (input[v] == '|' || input[v] == '&')
		{
			add_node(hs, input[v]);
			v++;
		}
	}

	line = split_string(input, ";|&");
	do {
		line = non_printed_char_swap(line, 1);
		end_node(hl, line);
		line = split_string(NULL, ";|&");
	} while (line != NULL);

}


/**
 * next_In_Line -  The function is mean to go to the
 * next command line stored
 * @l_s: sep list
 * @l_l: command line list
 * @dsh: data structure
 * Return: no return
 */
void next_In_Line(def **l_s, dap **l_l, shell_shell *dsh)
{
	int loop_s;
	def *ls_s;
	dap *ls_l;

	loop_s = 1;
	ls_s = *l_s;
	ls_l = *l_l;

	while (ls_s != NULL && loop_s)
	{
		if (dsh->status == 0)
		{
			if (ls_s->separator== '&' || ls_s->separator == ';')
				loop_s = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_s = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_s)
			ls_s = ls_s->next;
	}

	*l_s = ls_s;
	*l_l = ls_l;
}


/**
 * splityy - the function tokenizes the input string
 * @input: input(string).
 * Return: string splitted.
 */
char **splityy(char *input)
{
	size_t as;
	size_t v;
	char **tokens;
	char *token;

	as = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bs));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = split_string(input, TOK_DELIM);
	tokens[0] = token;

	for (v = 1; token != NULL; v++)
	{
		if (v == bs)
		{
			as += TOK_BUFSIZE;
			tokens = prmalloc(tokens, v, sizeof(char *) * as);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = split_string(NULL, TOK_DELIM);
		tokens[v] = token;
	}

	return (tokens);
}
