#include "shell.h"

/**
 * _strcpy - copie strings
 * @dst: destination
 * @src: source
 *
 * Return:  destination pointer 
 */
char *_strcpy(char *dst, char *src)
{
int i = 0;

if (dst == src || src == 0)
        return dst;
while (src[i])
{
dst[i] = src[i];
i++;
}
dst[i] = 0;
return dst;
}

/**
 * _strdup - duplicate strings
 * @str: string to duplicate
 *
 * Return:  duplicated string's pointer
 */
char *_strdup(const char *str)
{
int length = 0;
char *ret;

if (str == NULL)
return NULL;
while (*str++)
length++;
ret = malloc(sizeof(char) * (length + 1));
if (!ret)
return NULL;
for (length++; length--;)
ret[length] = *--str;
return ret;
}

/**
 * _puts - prints string's input 
 * @str: the string to print
 *
 * Return: Nothing
 */
void _puts(char *str)
{
int i = 0;

if (!str)
return;
while (str[i] != '\0')
{
_putchar(str[i]);
i++;
}
}

/**
 * _putchar - stdout is updated with the character C.
 * @c: The character to print
 *
 * Return: On success return 1.
 * On error, return -1 , errno is properly set.
 */
int _putchar(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(1, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return 1;
}
