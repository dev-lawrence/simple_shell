#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#include "shell.h"

#define MAX_ARGS 10

void executeCommand(char *command) {
    pid_t pid = fork();

    if (pid < 0) {
        /* Error occurred */
        write(STDERR_FILENO, "Fork failed\n", 12);
    } else if (pid == 0) {
        /* Child process */
        char *args[MAX_ARGS + 2];  /* +2 to account for the command and NULL terminator */
        int numArgs = 0;

        /* Tokenize the command string into arguments */
        char *token = strtok(command, " ");
        while (token != NULL && numArgs < MAX_ARGS) {
            args[numArgs++] = token;
            token = strtok(NULL, " ");
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
