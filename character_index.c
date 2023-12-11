#include "shell.h"

/**
 * countChar_rep - countChar_rep function counts the
 * repetitions of a char
 * @input: input string
 * @u: index
 * Return: repetitions
 */
int countChar_rep(char *input, int u)
{
	if (*(input - 1) == *input)
		return (countChar_rep(input - 1, u + 1));

	return (u);
}
/**
 * syntax_error - syntax_error function finds syntax errors
 * @input: input string
 * @u: index
 * @last: last character read
 * Return: index of error. 0 when there are no
 * errors
 */
int syntax_error(char *input, int u, char last)
{
	int d;

	d = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (syntax_error(input + 1, u + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (u);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (u);

		if (last == '|')
		{
			d = countChar_rep(input, 0);
			if (d == 0 || d > 1)
				return (u);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (u);

		if (last == '&')
		{
			d = countChar_rep(input, 0);
			if (d == 0 || d > 1)
				return (u);
		}
	}

	return (syntax_error(input + 1, u + 1, *input));
}
/**
 * char_index - char_index function finds index of the first char
 * @input: input string
 * @u: index
 * Return: 1 if there is an error else return 0.
 */
int char_index(char *input, int *u)
{
	for (*u = 0; input[*u]; *u += 1)
	{
		if (input[*u] == ' ' || input[*u] == '\t')
			continue;

		if (input[*u] == ';' || input[*u] == '|' || input[*u] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * split_lines - split_lines functions splits command lines according to
 * the separators ;, | and &, and executes them
 * @dsh: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int split_lines(shell_shell *dsh, char *input)
{

	def *x, *l_s;
	dap *y, *l_l;
	int myloop;

	i = NULL;
	w = NULL;

	addSeparators_and_cdLists(&i, &w, input);

	l_s = i;
	l_l = w;

	while (l_l != NULL)
	{
		dsh->input = l_l->line;
		dsh->args = splityy(dsh->input);
		myloop = kano(dsh);
		free(dsh->args);

		if (myloop == 0)
			break;

		nextInLine(&l_s, &l_l, dsh);

		if (l_l != NULL)
			l_l = l_l->next;
	}

	fee_list(&i);
	free_list(&w);

	if (myloop == 0)
		return (0);
	return (1);
}
/**
 * err_message - err_message function prints when a syntax error is found
 * @dsh: data structure
 * @input: input
 * @u: index
 * @bool: to control mg error
 * Return: no return
 */
void err_message(shell_shell *dsh, char *input, int u, int bool)
{
	char *mg, *mg2, *mg3, *e, *counter;
	int leth;

	if (input[u] == ';')
	{
		if (bool == 0)
			mg = (input[u + 1] == ';' ? ";;" : ";");
		else
			mg = (input[u - 1] == ';' ? ";;" : ";");
	}

	if (input[u] == '|')
		mg = (input[u + 1] == '|' ? "||" : "|");

	if (input[u] == '&')
		mg = (input[u + 1] == '&' ? "&&" : "&");

	mg2 = ": Syntax error: \"";
	mg3 = "\" unexpected\n";
	counter = int_toString(dsh->counter);
	leth = string_length(dsh->ichi[0]) + string_length(counter);
	leth += string_length(mg) + string_length(mg2) + string_length(mg3) + 2;

	e = malloc(sizeof(char) * (leth + 1));
	if (e == 0)
	{
		free(counter);
		return;
	}
	dup_string(e, dsh->ichi[0]);
	concate(e, ": ");
	concate(e, counter);
	concate(e, mg2);
	concate(e, mg);
	concate(e, mg3);
	concate(e, "\0");

	write(STDERR_FILENO, e, lth);
	free(e);
	free(counter);
}
