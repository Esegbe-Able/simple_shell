#include "shells.h"
/**
 * dup_str - dup_str function duplicates a string in
 * the heap memory.
 * @s: char pointer str
 * Return: the duplicated str
 */
char *dup_str(const char *s)
{
	char *fresh;
	size_t len;

	len = string_length(s);
	fresh = malloc(sizeof(char) * (len + 1));
	if (fresh == NULL)
		return (NULL);
	copy_info(fresh, s, len + 1);
	return (fresh);
}
/**
 * string_length - Returns the lengthght of a string.
 * @s: Type char pointer
 * Return: Always 0.
 */
int string_length(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
}
/**
 * compChar_str - compChar_str function compares
 * characters of strings
 * @string: the input string.
 * @delim: delimiter.
 * Return: 1 if are equals, 0 if not.
 */
int compChar_str(char string[], const char *delim)
{
	unsigned int i, w, y;

	i = 0;
	y = 0;
	while (string[i])
	{
		w = 0;
		while (delim[w])
		{
			if (string[i] == delim[w])
			{
				y++;
				break;
			}
			w++;
		}
		i++;
	}
	if (i == y)
		return (1);
	return (0);
}
/**
 * split_str - split_str function splits a string by some delimiter.
 * @string: input string.
 * @delim: delimiter.
 * Return: string splited.
 */
char *split_str(char string[], const char *delim)
{
	static char *split, *string_end;
	char *string_start;
	unsigned int v, bool;

	if (string != NULL)
	{
		if (compChar_str(string, delim))
			return (NULL);
		split = string; /*Store first address*/
		v = string_length(string);
		string_end = &string[v]; /*Store last address*/
	}
	string_start = split;
	if (string_start == string_end) /*Reaching the end*/
		return (NULL);

	for (bool = 0; *split; split++)
	{
		/*Breaking loop finding the next token*/
		if (split != string_start)
			if (*split && *(split - 1) == '\0')
				break;
		/*Replacing delimiter for null char*/
		for (v = 0; delim[v]; v++)
		{
			if (*split == delim[v])
			{
				*split = '\0';
				if (split == string_start)
					string_start++;
				break;
			}
		}
		if (bool == 0 && *split) /*String != Delim*/
			bool = 1;
	}
	if (bool == 0) /*String == Delim*/
		return (NULL);
	return (string_start);
}
