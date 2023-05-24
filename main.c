#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "shell.h"

#define MAX_COMMAND_LENGTH 100
/**
 * main - Entry point of the shell program
 * Description: This function serves as the entry point for the shell program.
 *              It reads the user input from stdin, executes the command,
 *              and displays the prompt for the next command.
 *              The loop continues until the end of file (Ctrl+D) is reached.
 *
 * Return: Always returns 0.
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
	executeCommand(command);

	}

	free(command);

	return (0);
}
