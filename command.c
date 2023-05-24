#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#include "shell.h"

#define MAX_ARGS 10
/**
 * executeCommand - Execute the given command
 * @command: The command to execute
 *
 * Description: This function is responsible for executing the given command
 *              in a child process. It tokenizes the command string into
 *              arguments, sets up the argument array, and uses execvp()
 *              to execute the command. If an error occurs, it writes an
 *              appropriate error message to stderr.
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
	int numArgs = 0;

	/* Tokenize the command string into arguments */
	char *token = strtok(command, " ");

	while (token != NULL && numArgs < MAX_ARGS)
	{
		args[numArgs++] = token;
		token = strtok(NULL, " ");
	}
		args[numArgs] = NULL;
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
