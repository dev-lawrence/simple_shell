#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
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
 * handleSetEnv - Handles the "setenv" command.
 * @args: The command arguments.
 * @numArgs: The number of arguments.
 */
void handleSetEnv(char **args, int numArgs);

/**
 * handleUnsetEnv - Handles the "unsetenv" command.
 * @args: The command arguments.
 * @numArgs: The number of arguments.
 */
void handleUnsetEnv(char **args, int numArgs);

/**
 * executeChildProcess - Executes the command in a child process.
 * @args: The command arguments.
 */
void executeChildProcess(char **args);

/**
 * executeCommand - Executes the given command in a child process
 * @command: The command to execute
 */
void executeCommand(char *command)
{
	char *args[MAX_ARGS + 2];
	int numArgs = splitCommand(command, args);

	if (numArgs > 0)
	{
		if (strcmp(args[0], "setenv") == 0)
		{
			handleSetEnv(args, numArgs);
		}
		else if (strcmp(args[0], "unsetenv") == 0)
		{
			handleUnsetEnv(args, numArgs);
		}
		else
		{
			executeChildProcess(args);
		}
	}
}

/**
 * handleSetEnv - Handles the "setenv" command.
 * @args: The command arguments.
 * @numArgs: The number of arguments.
 */
void handleSetEnv(char **args, int numArgs)
{
	if (numArgs != 3)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
	}
	else
	{
		if (setenv(args[1], args[2], 1) != 0)
		{
			fprintf(stderr, "Failed to set environment variable\n");
		}
	}
}

/**
 * handleUnsetEnv - Handles the "unsetenv" command.
 * @args: The command arguments.
 * @numArgs: The number of arguments.
 */
void handleUnsetEnv(char **args, int numArgs)
{
	if (numArgs != 2)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
	}
	else
	{
		if (unsetenv(args[1]) != 0)
		{
			fprintf(stderr, "Failed to unset environment variable\n");
		}
	}
}

/**
 * executeChildProcess - Executes the command in a child process.
 * @args: The command arguments.
 */
void executeChildProcess(char **args)
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
		execvp(args[0], args);
		/* execvp only returns if an error occurs */
		fprintf(stderr, "No such file or directory\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent process */
		wait(NULL);
	}
}
