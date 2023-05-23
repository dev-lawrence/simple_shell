#ifndef SHELL_H
#define SHELL_H
#include <string.h>

extern char **environ;

void display_prompt(void);
void executeCommand(char *command);
void exitShell(int status);
void printEnvironment(void);
ssize_t my_getline(char *command);

ssize_t readInputBuffer(void);
int hasBufferSpace(void);
char *findNewline(void);
void copyInputToCommand(char *command, size_t bytes_to_copy);

int splitCommand(char *command, char *args[]);

#endif  /* SHELL_H */
