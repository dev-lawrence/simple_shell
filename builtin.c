#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

extern char **environ;

void printEnvironment() {
    char **env = environ;
    while (*env) {
        printf("%s\n", *env);
        env++;
    }
}
