#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "shell.h"

#define MAX_COMMAND_LENGTH 100

int main() {
    char *command = NULL;
    size_t commandLength = 0;
    ssize_t bytesRead;

    while (1) {
        displayPrompt();

        bytesRead = getline(&command, &commandLength, stdin);

        if (bytesRead == -1) {
            /* End of file (Ctrl+D) reached */
            write(STDOUT_FILENO, "\n", 1);
            break;
        }

        /* Remove the trailing newline character */
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0) {
            exitShell();
            break;
        }
        else if (strcmp(command, "env") == 0) {
            printEnvironment();
            continue;
        }

        executeCommand(command);
    }

    free(command);

    return 0;
}
