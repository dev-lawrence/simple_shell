#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

/**
 * printEnvironment - Prints the environment variables.
 * @environ: The array of environment variables.
 */
void printEnvironment(char **environ)
{
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
