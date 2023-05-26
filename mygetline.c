#include <unistd.h>
#include <string.h>
#include "shell.h"

#define BUFFER_SIZE 1024

static char input_buf[BUFFER_SIZE];
static size_t input_buf_index;
static size_t bytes_in_buf;

/**
 * read_input_buf - Reads input from the buffer into the input buffer.
 *
 * This function reads input from the buffer into the input buffer. It uses
 * the read() function to read from the standard input and stores the read
 * data in the input buffer.
 *
 * Return: The number of bytes read from the buffer.
 */
ssize_t read_input_buf(void)
{
	input_buf_index = 0;
	bytes_in_buf = read(STDIN_FILENO, input_buf, BUFFER_SIZE);
	return (bytes_in_buf);
}

/**
 * has_buf_space - Checks if there is space available in the input buffer.
 *
 * This function checks if there is space available in the input buffer
 * for reading more data. It compares the current index of the input buffer
 * with the number of bytes in the buffer to determine if there is space
 * available.
 *
 * Return: 1 if there is space available, 0 otherwise.
 */
int has_buf_space(void)
{
	return (input_buf_index < bytes_in_buf);
}

/**
 * find_newline - Finds the next newline character in the input buffer.
 *
 * This function searches for the next newline character ('\n') in the
 * input buffer starting from the current index. It returns a pointer to
 * the next newline character if found, or NULL if not found.
 *
 * Return: A pointer to the next newline character, or NULL if not found.
 */
char *find_newline(void)
{
	return (strchr(input_buf + input_buf_index, '\n'));
}

/**
 * copy_input_to_cmd - copies input from the input buffer to command buffer.
 *
 * This function copies the input from the input buffer to the command buffer.
 * It takes a destination buffer 'cmd' and the number of bytes to copy from
 * the input buffer 'bytes_to_copy'. The function uses memcpy() to copy the
 * data and appends a null terminator at the end of the copied data.
 *
 * @cmd: The destination buffer to copy the input to.
 * @bytes_to_copy: The number of bytes to copy from the input buffer.
 */
void copy_input_to_cmd(char *cmd, size_t bytes_to_copy)
{
	memcpy(cmd, input_buf + input_buf_index, bytes_to_copy);
	cmd[bytes_to_copy] = '\0';
}

/**
 * my_getline - Reads input from the user into the command buffer.
 *
 * This function reads input from the user into the command buffer. It reads
 * data from the input buffer and checks for newline characters. If a newline
 * character is found, the function copies the data until the newline character
 * to the command buffer. If no newline character is found, the function copies
 * the remaining data in the input buffer to the command buffer.
 *
 * @cmd: The destination buffer for storing the input.
 *
 * Return: The total number of bytes read.
 */
ssize_t my_getline(char *cmd)
{
	ssize_t total_bytes_read = 0;
	char *newline;
	size_t remaining_bytes;

	while (1)
	{
	if (!has_buf_space())
	{
	if (read_input_buf() <= 0)
	break;

	total_bytes_read += bytes_in_buf;
	}

	newline = find_newline();
	if (newline != NULL)
	{
		size_t bytes_newline = newline - (input_buf + input_buf_index) + 1;

		copy_input_to_cmd(cmd, bytes_newline);
		input_buf_index += bytes_newline;
		total_bytes_read -= bytes_newline;
		return (total_bytes_read);
	}

	remaining_bytes = bytes_in_buf - input_buf_index;
	copy_input_to_cmd(cmd, remaining_bytes);
	input_buf_index = bytes_in_buf;
	}
	return (total_bytes_read);
}
