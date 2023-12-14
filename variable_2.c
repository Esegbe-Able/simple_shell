#include "shells.h"
/**
 * concate_nate - The concate_nate function's job is to
 * concatenate two strings
 * @dest: character pointer the destination of the copied string
 * @src: character pointer the source of string
 * Return: dest
 */
char *concate_nate(char *dest, const char *src)
{
	int s;
	int n;

	for (s = 0; dest[s] != '\0'; s++)
		;

	for (n = 0; src[n] != '\0'; n++)
	{
		dest[s] = src[n];
		s++;
	}

	dest[s] = '\0';
	return (dest);
}
/**
 * *dup_string - This function duplicates the string
 * pointed to by the source.
 * @dest: points to the destination of the dulpicated string
 * @src: points to the source of string
 * Return: dest.
 */
char *dup_string(char *dest, char *src)
{

	size_t y;

	for (y = 0; src[y] != '\0'; y++)
	{
		dest[y] = src[y];
	}
	dest[y] = '\0';

	return (dest);
}
/**
 * comp_are - The function's work is to compare two strings.
 * @s1: type str compared
 * @s2: type str compared
 * Return: Always 0.
 */
int comp_are(char *s1, char *s2)
{
	int w;

	for (w = 0; s1[w] == s2[w] && s1[w]; w++)
		;

	if (s1[w] > s2[w])
		return (1);
	if (s1[w] < s2[w])
		return (-1);
	return (0);
}
/**
 * string_locate - string_locate locates a char in a string,
 * @s: string.
 * @c: char.
 * Return: the pointer to the first occurrence of the character c.
 */
char *string_locate(char *s, char c)
{
	unsigned int q = 0;

	for (; *(s + q) != '\0'; q++)
		if (*(s + q) == c)
			return (s + q);
	if (*(s + q) == c)
		return (s + q);
	return ('\0');
}
/**
 * take_string- take_string acquires the length
 * of a prefix substring.
 * @s: initial
 * @rec: accepted bytes.
 * Return: numb of accepted bytes.
 */
int take_string(char *s, char *rec)
{
	int r, e, bool;

	for (r = 0; *(s + r) != '\0'; r++)
	{
		bool = 1;
		for (e = 0; *(rec + e) != '\0'; e++)
		{
			if (*(s + r) == *(rec + e))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (r);
}
