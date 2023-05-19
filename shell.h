#ifndef SHELL_H
#define SHELL_H

extern char **environ;

void display_prompt(void);
void executeCommand(char *command);
void exitShell(void);
void printEnvironment(void);

#endif  /* SHELL_H */
