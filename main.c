#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

/**
 * handle_command - Handle the given command
 * @command: The command to handle
 *
 * Description: This function forks a child process and executes the given
 *              command using `execve()`. If the command is not found or there
 *              is an error during forking or execution, appropriate error
 *              messages are displayed.
 */
void handle_command(char *command);

/**
 * execute_command - Execute the given command
 * @path: The path of the command to execute
 *
 * Description: This function sets up the arguments array and uses `execve()`
 *              to execute the command. If there is an error during execution,
 *              an appropriate error message is displayed.
 */
void execute_command(char *path);

/**
 * print_command_not_found - Print "Command not found" message
 * @command: The command that was not found
 *
 * Description: This function prints an error message indicating that the
 *              given command was not found.
 */
void print_command_not_found(const char *command);

/**
 * main - Entry point of the shell program
 *
 * Description: This function serves as the entry point for the shell program.
 *              It reads the user input from stdin, forks a child process,
 *              and executes the command using execve(). If the command is
 *              not found or there is an error during forking or execution,
 *              appropriate error messages are displayed.
 *
 * Return: Always returns 0.
 */
int main(void)
{
	char *command = NULL;
	size_t bufsize = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");

		if (getline(&command, &bufsize, stdin) == -1)
		{
			/* Handle end of file (Ctrl+D) */
			printf("\n");
			break;
		}

		/* Remove the trailing newline character */
		command[strcspn(command, "\n")] = '\0';

		handle_command(command);
	}

	free(command);
	return (0);
}

/**
 * handle_command - Handle the given command
 * @command: The command to handle
 *
 * Description: This function forks a child process and executes the given
 *              command using `execve()`. If the command is not found or there
 *              is an error during forking or execution, appropriate error
 *              messages are displayed.
 */
void handle_command(char *command)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/* Child process */
		char *path = strtok(command, " ");

		if (access(path, X_OK) == 0)
		{
			execute_command(path);
		}
		else
		{
			print_command_not_found(path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		waitpid(pid, NULL, 0);
	}
}

/**
 * execute_command - Execute the given command
 * @path: The path of the command to execute
 *
 * Description: This function sets up the arguments array and uses `execve()`
 *              to execute the command. If there is an error during execution,
 *              an appropriate error message is displayed.
 */
void execute_command(char *path)
{
	char **args = malloc(sizeof(char *) * 2);

	if (args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	args[0] = path;
	args[1] = NULL;


	execve(path, args, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}

/**
 * print_command_not_found - Print "Command not found" message
 * @command: The command that was not found
 *
 * Description: This function prints an error message indicating that the
 *              given command was not found.
 */
void print_command_not_found(const char *command)
{
	fprintf(stderr, "Command not found: %s\n", command);
}
