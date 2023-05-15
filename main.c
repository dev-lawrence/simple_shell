#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "shell.h"

/**
 * main - Entry point
 *
 * Return: 0 on success, otherwise error code
 */
int main(void)
{
	char *command = NULL;
	size_t commandLength = 0;
	ssize_t bytesRead;

	while (1)
	{
		displayPrompt();

		bytesRead = getline(&command, &commandLength, stdin);

		if (bytesRead == -1)
		{
			/* End of file (Ctrl+D) reached */
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		/* Remove the trailing newline character */
		command[strcspn(command, "\n")] = '\0';

		executeCommand(command);
	}

	free(command);

	return (0);
}
