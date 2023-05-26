#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

/**
 * displayPrompt - Displays the prompt "#cisfun$ "
 * Description: This function is responsible for displaying the prompt
 *              "#cisfun$ " to the user.
 *              It uses the write() function to write the prompt to the
 *              standard output file descriptor.
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
