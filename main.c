#include "simple_shell.h"

/**
 * main - Entry point of the program
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = {INFO_INIT}; /* Initializing info array */
	int fd = 2; /* File descriptor initialized to standard error */

	/* Move the value of fd to the register and add 3 to it */
	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		/* Open the file provided as an argument in read-only mode */
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			/* Handle error cases */
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd; /* Set the file descriptor in info structure */
	}

	populate_env_list(info); /* Populate environment list */
	read_history(info); /* Read command history */
	hsh(info, av); /* Call the shell function */
	return (EXIT_SUCCESS);
}
