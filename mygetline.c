#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

ssize_t myGetline(char **lineptr, size_t *n, FILE *stream) {
    static char buffer[BUFFER_SIZE];
    static size_t bufferIndex = 0;
    static ssize_t bytesRead = 0;

    ssize_t lineLength = 0;
    char *bufferPtr = buffer + bufferIndex;
    char *newlinePtr;

    while (1) {
        newlinePtr = strchr(bufferPtr, '\n');
        if (newlinePtr != NULL) {
            /* Found a newline character */
            *newlinePtr = '\0';
            lineLength += newlinePtr - bufferPtr + 1;
            if (lineLength > (ssize_t)(*n)) {
                /* Resize the buffer if necessary */
                *n = lineLength;
                *lineptr = realloc(*lineptr, *n);
                if (*lineptr == NULL) {
                    return -1;  /* Error: Failed to allocate memory */
                }
            }
            strncpy(*lineptr + lineLength - (size_t)(newlinePtr - bufferPtr) - 1, bufferPtr, (size_t)(newlinePtr - bufferPtr) + 1);
            bufferIndex += newlinePtr - bufferPtr + 1;
            return lineLength - 1;  /* Return the length of the line (excluding the newline character) */
        } else {
            /* No newline character found in the current buffer, need to read more data */
            if (bytesRead == 0) {
                /* End of file reached */
                if (lineLength == 0) {
                    return -1;  /* No more input available */
                } else {
                    (*lineptr)[lineLength] = '\0';
                    return lineLength;  /* Return the length of the line */
                }
            } else {
                /* Shift the remaining data to the beginning of the buffer */
                memmove(buffer, bufferPtr, bytesRead);
                bufferIndex = 0;
            }

            bytesRead = read(fileno(stream), buffer + bytesRead, BUFFER_SIZE - bytesRead);
            if (bytesRead == -1) {
                return -1;  /* Error: Failed to read data */
            }
        }

        bufferPtr = buffer;
    }
}
