#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "shell.h"

#define MAX_COMMAND_LENGTH 100

char *getHomeDirectory();

/**
 * changeDirectory - Changes the current working directory.
 * @directory: The directory to change to.
 */
void changeDirectory(const char *directory)
{
	char *home = getHomeDirectory();
	const char *targetDir = NULL;

	if (directory == NULL)
	{
		targetDir = home;
	}
	else if (strcmp(directory, "-") == 0)
	{
		const char *previousDir = getenv("OLDPWD");

	if (previousDir == NULL)
	{
		fprintf(stderr, "cd: OLDPWD not set\n");
		return;
	}
		targetDir = previousDir;
		printf("%s\n", targetDir);
	}
	else
	{
		targetDir = directory;
	}

	if (chdir(targetDir) != 0)
	{
		fprintf(stderr, "cd: No such file or directory: %s\n", targetDir);
		return;
	}

	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", targetDir, 1);
}

/**
 * getHomeDirectory - Retrieves the home directory path.
 *
 * Return: The home directory path as a string.
 */
char *getHomeDirectory()
{
	char *home = getenv("HOME");

	if (home == NULL)
	{
		fprintf(stderr, "cd: HOME not set\n");
		exit(EXIT_FAILURE);
	}
	return (home);
}

/**
 * processCommand - Process a command in the shell.
 *
 * @command: The command to process.
 */
void processCommand(const char *command);

/**
 * handleExitCommand - Handle the "exit" command in the shell.
 *
 * @command: The exit command with optional arguments.
 */
void handleExitCommand(const char *command);

/**
 * handleEnvCommand - Handle the "env" command in the shell.
 */
void handleEnvCommand(void);

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

	if (strncmp(command, "exit", 4) == 0)
	{
		handleExitCommand(command);
		break;
	}

	else if (strncmp(command, "setenv", 6) == 0 ||
		strncmp(command, "unsetenv", 8) == 0)
	{
		processCommand(command);
	}

	else if (strcmp(command, "env") == 0)
	{
		handleEnvCommand();
	}

	else if (strncmp(command, "cd", 2) == 0)
	{
		char *directory = strtok(command, " ");

		directory = strtok(NULL, " ");
		changeDirectory(directory);
	}

		else
		{
		executeCommand(command);
		}
	}

	return (0);
}

/**
 * processCommand - Process a command in the shell.
 *
 * @command: The command to process.
 */
void processCommand(const char *command)
{
	char *mutableCommand = strdup(command);

	executeCommand(mutableCommand);
	free(mutableCommand);
}

/**
 * handleExitCommand - Handle the "exit" command in the shell.
 *
 * @command: The exit command with optional arguments.
 */
void handleExitCommand(const char *command)
{
    /* Check if command has additional arguments */
	if (strlen(command) > 4)
	{

	int status = atoi(command + 5);

	exitShell(status);
	}
	else
	{
	exitShell(0);
	}
}

/**
 * handleEnvCommand - Handle the "env" command in the shell.
 */
void handleEnvCommand(void)
{
	printEnvironment();
}
