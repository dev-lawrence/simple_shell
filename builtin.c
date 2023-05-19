#include <stdlib.h>
#include <unistd.h>
#include "shell.h"


/**
 * printEnvironment - Prints the environment variables
 */
void printEnvironment(void)
{
	char **env = environ;

	while (*env != NULL)
	{

	char *currentEnv = *env;

	while (*currentEnv != '\0')
	{
		write(1, currentEnv, 1);
		currentEnv++;
	}
	write(1, "\n", 1);
		env++;
	}
}
