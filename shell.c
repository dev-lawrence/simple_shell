#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

void displayPrompt() {
    write(STDOUT_FILENO, "#cisfun$ ", 9);
}

void executeCommand(char *command) {
    pid_t pid = fork();

    if (pid < 0) {
        /* Error occurred */
        write(STDERR_FILENO, "Fork failed\n", 12);
    } else if (pid == 0) {
        /* Child process */
        char **args = (char **)malloc(2 * sizeof(char *));
        args[0] = command;
        args[1] = NULL;
        
        execve(command, args, NULL);

        /* execve only returns if an error occurs */
        write(STDERR_FILENO, "No such file or directory\n", 26);
        exit(EXIT_FAILURE);
    } else {
        /* Parent process */
        wait(NULL);
    }
}
