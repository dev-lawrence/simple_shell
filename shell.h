#include <stdio.h>
#ifndef SHELL_H
#define SHELL_H

void displayPrompt();
void executeCommand(char *command);
void exitShell();
void printEnvironment();
ssize_t myGetline(char **lineptr, size_t *n, FILE *stream);

#endif  /* SHELL_H */
