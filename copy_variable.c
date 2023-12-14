#include "shells.h"

/**
 * copy_info - copy_s function copies information betwixt void pointers.
 * @newptr: dest pointer
 * @ptr: source pointer.
 * @size: size of new pointer.
 * Return: no return.
 */

void copy_info(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int s;

	for (s = 0; s < size; s++)
		char_newptr[s] = char_ptr[s];
}
/**
 * *realloc_mem - This function is meant to  reallocate the memory block.
 * @ptr: pointer to the memory that has been previously realocated
 * @old_size: size of previously realocated
 * @new_size: new size of the new memory block(in bytes).
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *realloc_mem(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);

	if (new_size < old_size)
		copy_info(new_ptr, ptr, new_size);
	else
		copy_info(new_ptr, ptr, old_size);

	free(ptr);
	return (new_ptr);
}




/**
 * del_com - The del_com function deletes comments from the input
 * @in: input (In string)
 * Return: input without comments
 */
char *del_com(char *in)
{
	int v, v_to;

	v_to = 0;
	for (v = 0; in[v]; v++)
	{
		if (in[v] == '#')
		{
			if (v == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[v - 1] == ' ' || in[v - 1] == '\t' || in[v - 1] == ';')
				v_to = v;
		}
	}

	if (v_to != 0)
	{
		in = realloc_mem(in, v, v_to + 1);
		in[v_to] = '\0';
	}

	return (in);
}

/**
 * loop_shell - loop shell function loops the shell
 * @dsh: data (av, input, args)
 * Return: no return.
 */
void loop_shell(shells_shell *dsh)
{
	int looop, aff;
	char *input;

	for (looop = 1; looop == 1;)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = READLINE(&aff);
		if (aff != -1)
		{
			input = del_com(input);
			if (input == NULL)
				continue;

			if (caseint_function(dsh, input) == 1)
			{
				dsh->status = 2;
				free(input);
				continue;
			}
			input = replace_var(input, dsh);
			looop = split(dsh, input);
			dsh->counter += 1;
			free(input);
		}
		else
		{
			looop = 0;
			free(input);
		}
	}
}

/**
 * ptr_malloc -  **ptr_malloc pointer function reallocates a
 * memory block of a double pointer.
 * @ptr: double pointer to the previously allocated memory.
 * @old_size: size of the  allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
char **ptr_malloc(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int s;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (s = 0; s < old_size; s++)
		newptr[s] = ptr[s];

	free(ptr);

	return (newptr);
}
