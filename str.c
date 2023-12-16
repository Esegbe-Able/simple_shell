#include "shell.h"

/**
 * _strlength - _strlength function returns the length of a string
 * @s: string's length to check
 *
 * Return: integer length of string
 */
int _strlength(char *s)
{
	int j = 0;

	if (!s)
		return (0);

	while (*s++)
		j++;
	return (j);
}

/**
 * _strComp - _strComp performs lexicogarphic comparison of two strangs.
 * @s1: first string
 * @s2: second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strComp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * start_with - start_with function checks if needle starts with haystack
 * @haystack: string to search
 * @needle: substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *start_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _str_concat - *_str_concat concatenates two strings
 * @dest: destination buffer
 * @src: source
 *
 * Return: pointer to destination buffer
 */
char *_str_concat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
