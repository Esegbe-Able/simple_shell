#include "shell.h"

/**
 * free_ptr -  free_ptr function frees a pointer
 * and NULLs the address
 * @ptr: address of pointer to be free
 *
 * Return: 1 if freed, otherwise 0.
 */
int free_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
