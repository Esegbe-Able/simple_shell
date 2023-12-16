#include "shell.h"

/**
 **fill_memset - *fill_memset function  fills memory with a constant byte
 *@s: pointer to the memory area
 *@b: byte to fill *s with
 *@n: amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *fill_memset(char *s, char b, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
		s[j] = b;
	return (s);
}

/**
 * free_stri - free_stri function frees a string of strings
 * @pp: string of strings
 */
void free_stri(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * realloc_mem - realloc_mem's function reallocates a block of memory
 * @ptr: poits to previous malloc'ated block
 * @old_size: size of previous block
 * @new_size: size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *realloc_mem(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
