#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

void displayPrompt() {
    write(STDOUT_FILENO, "#cisfun$ ", 9);
}
