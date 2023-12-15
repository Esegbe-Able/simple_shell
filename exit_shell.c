#include "shell.h"

/**
 **_stringcpy - _stringcpy pointer function copies a string
 *@dest: destination string to be copied to
 *@src: the source
 *@n: the number of characters to be copied
 *Return: concatenated string
 */
char *_stringcpy(char *dest, char *src, int n)
{
	int j, k;
	char *s = dest;
	
	j = 0;
	while (src[j] != '\0' && j < n - 1)
	{
		dest[j] = src[j];
		j++;
	}
        if (j < n)
        {
                k = j;
                while (k < n)
                {
                        dest[k] = '\0';
                        k++;/**
 **_strn_concat - _strn_concat pointer function concatenates two strings
 *@dest: first string
 *@src: second string
 *@n: the number of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strn_concat(char *dest, char *src, int n)
{
        int j, k;
        char *s = dest;

        j = 0;
        k = 0;
        while (dest[j] != '\0')
                j++;
        while (src[k] != '\0' && k < n)
        {
                dest[j] = src[k];
                j++;
                k++;
        }
        if (k < n)
                dest[j] = '\0';
        return (s);
}

/**
 **locChar_str - *locChar_strv function locates a character in a string
 *@s: string to parse
 *@c: char to look for
 *Return: (s) a pointer to the memory area s
 */
char *locChar_str(char *s, char c)
{
        do {
                if (*s == c)
                        return (s);
        } while (*s++ != '\0');

        return (NULL);
}
                }
        }
        return (s);
}
