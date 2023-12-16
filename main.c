#include "shell.h"

/**
 * main - entry point of the function
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int gd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (gd)
		: "r" (gd));

	if (ac == 2)
	{
		gd = open(av[1], O_RDONLY);
		if (gd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				print_InpStr(av[0]);
				print_InpStr(": 0: Can't open ");
				print_InpStr(av[1]);
				write_char('\n');
				write_char(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = gd;
	}
	pop_env_list(info);
	read_hist(info);
	hshh(info, av);
	return (EXIT_SUCCESS);
}
