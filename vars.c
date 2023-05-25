#include "shell.h"

/**
 * is_chain - check to see if the current char in the buffer is a chain delimiter
 * @info: parameter struct
 * @buf: char buffer
 * @p: current position's address in buffer
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int is_chain(Info *info, char *buf, size_t *p)
{
    size_t j = *p;

    if (buf[j] == '|' && buf[j + 1] == '|')
    {
        buf[j] = 0;
        j++;
        info->commandBufferType = CMD_OR;
    }
    else if (buf[j] == '&' && buf[j + 1] == '&')
    {
        buf[j] = 0;
        j++;
        info->commandBufferType = CMD_AND;
    }
    else if (buf[j] == ';') /* found end of this command */
    {
        buf[j] = 0; /* replace semicolon with null */
        info->commandBufferType = CMD_CHAIN;
    }
    else
        return 0;
    *p = j;
    return 1;
}

/**
 * check_chain - based on the previous status, we should continue the chain.
 * @info: parameter struct
 * @buf: char buffer
 * @p: current position's address in buffer
 * @i: beginning place in buffer
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(Info *info, char *buf, size_t *p, size_t i, size_t len)
{
    size_t j = *p;

    if (info->commandBufferType == CMD_AND)
    {
        if (info->status)
        {
            buf[i] = 0;
            j = len;
        }
    }
    if (info->commandBufferType == CMD_OR)
    {
        if (!info->status)
        {
            buf[i] = 0;
            j = len;
        }
    }

    *p = j;
}

/**
 * replace_alias - substitutes a tokenized string's aliases
 * @info: parameter struct
 *
 * Return: 1 if replaced, else 0
 */
int replace_alias(Info *info)
{
    int i;
    List *node;
    char *p;

    for (i = 0; i < 10; i++)
    {
        node = node_starts_with(info->alias, info->arguments[0], '=');
        if (!node)
            return 0;
        free(info->arguments[0]);
        p = _strchr(node->string, '=');
        if (!p)
            return 0;
        p = _strdup(p + 1);
        if (!p)
            return 0;
        info->arguments[0] = p;
    }
    return 1;
}

/**
 * replace_vars - substitutes the tokenized string's vars
 * @info: parameter struct
 *
 * Return: 1 if replaced, else 0
 */
int replace_vars(Info *info)
{
    int i = 0;
    List *node;

    for (i = 0; info->arguments[i]; i++)
    {
        if (info->arguments[i][0] != '$' || !info->arguments[i][1])
            continue;

        if (!_strcmp(info->arguments[i], "$?"))
        {
            replace_string(&(info->arguments[i]),
                           _strdup(convert_number(info->status, 10, 0)));
            continue;
        }
        if (!_strcmp(info->arguments[i], "$$"))
        {
            replace_string(&(info->arguments[i]),
                           _strdup(convert_number(getpid(), 10, 0)));
            continue;
        }
        node = node_starts_with(info->env, &info->arguments[i][1], '=');
        if (node)
        {
            replace_string(&(info->arguments[i]),
                           _strdup(_strchr(node->string, '=') + 1));
            continue;
        }
        replace_string(&info->arguments[i], _strdup(""));
    }
    return 0;
}

/**
 * replace_string - string replacement
 * @old: string's address
 * @new: new string
 *
 * Return: 1 if replaced, else 0
 */
int replace_string(char **old, char *new)
{
    free(*old);
    *old = new;
    return 1;
}
