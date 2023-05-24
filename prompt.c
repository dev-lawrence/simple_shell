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
void displayPrompt(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", 9);
}
