#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

/**
 * display_prompt - Displays the prompt "#cisfun$ "
 */
void display_prompt(void)
{
	ssize_t len = sizeof("#cisfun$ ") - 1;
	ssize_t bytes_written = write(STDOUT_FILENO, "#cisfun$ ", len);

	if (bytes_written != len)
	{
	perror("Write error");
	exit(EXIT_FAILURE);
	}
}
