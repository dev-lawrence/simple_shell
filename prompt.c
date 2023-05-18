#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

/**
 * displayPrompt - Displays the shell prompt
 */
void displayPrompt(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", 9);
}
