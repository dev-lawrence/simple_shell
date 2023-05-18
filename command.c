#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARGS 10

void executeCommand(char *command) {
    pid_t pid;
    char *args[MAX_ARGS + 2];  /* +2 to account for the command and NULL terminator */
    int numArgs = 0;
    char *token = command;
    char *argStart, *argEnd;
    int argLength;

    pid = fork();

    if (pid < 0) {
        /* Error occurred */
        write(STDERR_FILENO, "Fork failed\n", 12);
    } else if (pid == 0) {
        /* Child process */
        while (*token != '\0' && numArgs < MAX_ARGS) {
            while (*token == ' ') {
                token++;  /* Skip leading spaces */
            }

            if (*token == '\0') {
                break;  /* Reached the end of the command string */
            }

            argStart = token;  /* Start of the current argument */

            while (*token != ' ' && *token != '\0') {
                token++;  /* Find the end of the current argument */
            }

            argEnd = token - 1;  /* End of the current argument */

            argLength = argEnd - argStart + 1;
            args[numArgs] = (char *)malloc(argLength + 1);  /* Allocate memory for the argument string */
            strncpy(args[numArgs], argStart, argLength);
            args[numArgs][argLength] = '\0';  /* Null-terminate the argument string */

            numArgs++;
        }
        args[numArgs] = NULL;  /* Set the last element to NULL to terminate the arguments list */

        execvp(args[0], args);

        /* execvp only returns if an error occurs */
        write(STDERR_FILENO, "No such file or directory\n", 26);
        exit(EXIT_FAILURE);
    } else {
        /* Parent process */
        wait(NULL);
    }
}
