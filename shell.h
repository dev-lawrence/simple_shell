#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void displayPrompt();
void executeCommand(char *command);
void printEnvironment();
void exitShell(int status);

ssize_t myGetline(char **lineptr, size_t *n, FILE *stream);

#endif /* SHELL_H */
