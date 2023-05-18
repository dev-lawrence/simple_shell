#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "parse_arguments.h"

void executeCommand(char *command)
{
    pid_t pid;
    char *args[MAX_ARGS + 2]; /* +2 to account for the command and NULL terminator */
    int numArgs = 0;

    pid = fork();

    if (pid < 0)
    {
        /* Error occurred */
        write(STDERR_FILENO, "Fork failed\n", 12);
    }
    else if (pid == 0)
    {
        /* Child process */
        parseArguments(command, args, &numArgs);

        /* Check if it's the exit command */
        if (strcmp(args[0], "exit") == 0)
        {
            /*  Get the status argument */
            int status = 0;
            if (numArgs > 1)
            {
                status = atoi(args[1]); /* Convert the status argument to an integer */
            }
            exit(status); /* Exit the shell with the provided status */
        }

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
