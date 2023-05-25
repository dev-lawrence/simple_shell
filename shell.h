#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1
#define READ_BUFFER_SIZE 1024

#define COMMAND_NORMAL 0
#define COMMAND_OR 1
#define COMMAND_AND 2
#define COMMAND_CHAIN 3

#define CONVERT_TO_LOWERCASE 1
#define CONVERT_TO_UNSIGNED 2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE ".simple_shell_history"
#define HISTORY_MAX 4096

extern char **environ;

typedef struct StringList {
    int number;
    char *string;
    struct StringList *next;
} List;

typedef struct PassInfo {
    char *argument;
    char **arguments;
    char *path;
    int argumentCount;
    unsigned int lineCount;
    int errorNumber;
    int lineCountFlag;
    char *fileName;
    List *environment;
    List *history;
    List *alias;
    char **environmentVariables;
    int environmentChanged;
    int status;
    char **commandBuffer;
    int commandBufferType;
    int readFd;
    int historyCount;
} Info;

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

void findCommand(Info *);
void forkCommand(Info *);
int shell(Info *, char **);
int findBuiltin(Info *);

char *duplicateChars(char *, int, int);
int isCommand(Info *, char *);
char *findPath(Info *, char *, char *);

int loopShell(char **);

int putFileDescriptor(char c, int fd);
int putStringToFileDescriptor(char *str, int fd);
void errorPuts(char *);
int errorPutChar(char);

int stringLength(char *);
char *startsWith(const char *, const char *);
int compareStrings(char *, char *);
char *concatenateStrings(char *, char *);

char *copyString(char *, char *);
void standardPuts(char *);
char *duplicateString(const char *);
int standardPutChar(char);

char *findCharacter(char *, char);
char *copySubstring(char *, char *, int);
char *concatenateSubstring(char *, char *, int);

char **splitStringWithDelimiter(char *, char);
char **splitString(char *, char *);

void freeMemory(char **);
void *reallocateMemory(void *, unsigned int, unsigned int);
char *setMemory(char *, char, unsigned int);

int freeBlock(void **);

int isDelimiter(char, char *);
int isAlphabetical(int);
int isInteractive(Info *);
int stringToInteger(char *);

int printDecimal(int, int);
char *convertNumber(long int, int, int);
int errorStringToInteger(char *);
void removeComments(char *);
void printErrorMessage(Info *, char *);

int changeDirectory(Info *);
int showHelp(Info *);
int exitShellCommand(Info *);

int defineAlias(Info *);
int showHistory(Info *);

int getInput(Info *, char **, size_t *);
ssize_t readInput(Info *);
void signalHandler(int);

void freeInfo(Info *, int);
void clearInfo(Info *);
void setInfo(Info *, char **);

int showEnvironment(Info *);
int setEnvironment(Info *);
int unsetEnvironment(Info *);
int populateEnvironmentList(Info *);
char *getEnvironment(Info *, const char *);

int unsetEnvironmentVariable(Info *, char *);
int setEnvironmentVariable(Info *, char *, char *);
char **getEnvironmentVariables(Info *);

int buildHistoryList(Info *info, char *buffer, int lineCount);
int renumberHistory(Info *info);
char *getHistoryFile(Info *info);
int writeHistory(Info *info);
int readHistory(Info *info);

size_t printStringList(const List *);
int deleteNodeAtIndex(List **, unsigned int);
List *addNode(List **, const char *, int);
List *addNodeAtEnd(List **, const char *, int);
void freeList(List **);

size_t printList(const List *);
List *findNodeStartsWith(List *, char *, char);
ssize_t getNodeIndex(List *, List *);
size_t getListLength(const List *);
char **listToStrings(List *);
void checkCommandChain(Info *, char *, size_t *, size_t, size_t);
int replaceAlias(Info *);
int replaceString(char **, char *);
int replaceVariables(Info *);
int isCommandChain(Info *, char *, size_t *);

#endif /* SHELL_H */

