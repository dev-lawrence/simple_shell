#include <stdlib.h>
#include "shell.h"

/**
 * exitShell - Exits the shell program
 * @status: The exit status code
 *
 * This function terminates the shell program with a status code of 0.
 */
void exitShell(int status)
{
	exit(status);
}
