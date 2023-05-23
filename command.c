#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#include "shell.h"

#define MAX_ARGS 10
/**
 * splitCommand - Tokenizes the command string into arguments
 * @command: The command to tokenize
 * @args: An array to store the arguments
 *
 * Return: The number of arguments
 */
int splitCommand(char *command, char *args[])
{
	int numArgs = 0;
	char *token;
	const char *delimiters = " \t\n";
	char *saveptr;

	token = strtok_r(command, delimiters, &saveptr);
	while (token != NULL && numArgs < MAX_ARGS)
	{
	args[numArgs++] = token;
	token = strtok_r(NULL, delimiters, &saveptr);
	}
	args[numArgs] = NULL;

	return (numArgs);
}

/**
 * executeCommand - Executes the given command in a child process
 * @command: The command to execute
 */
void executeCommand(char *command)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		/* Error occurred */
		write(STDERR_FILENO, "Fork failed\n", 12);
	}
	else if (pid == 0)
	{
		/* Child process */
		char *args[MAX_ARGS + 2];

		/* Tokenize the command string into arguments */
		splitCommand(command, args);

		 execvp(args[0], args);


		/* execvp only returns if an error occurs */
		write(STDERR_FILENO, "No such file or directory\n", 26);
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent process */
		wait(NULL);
	}
}
