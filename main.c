#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "shell.h"

#define MAX_COMMAND_LENGTH 100

/**
 * main - Entry point of the shell program
 *
 * This function implements a basic shell that repeatedly prompts the user for
 * commands, reads the input, and executes the corresponding commands.
 *
 * Return: Always returns 0.
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	ssize_t bytesRead;

	while (1)
	{
		display_prompt();
		bytesRead = my_getline(command);

	if (bytesRead == -1)
	{
		/* End of file (Ctrl+D) reached */
		write(STDOUT_FILENO, "\n", 1);
		break;
	}
	/* Remove the trailing newline character */

	command[strcspn(command, "\n")] = '\0';

	if (strcmp(command, "exit") == 0)
	{
		exitShell();
		break;
	}
	else if (strcmp(command, "env") == 0)
	{
		printEnvironment();
		continue;
	}
	executeCommand(command);
	}

	return (0);
}
