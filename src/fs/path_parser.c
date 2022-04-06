/**
 * @file path_parser.c
 * @author James Carr
 * @brief
 * @version 0.1
 * @date 05-04-2022
 *
 * Function implementations for parsing and tokenising path strings.  
 * Tokens and drive number are stored in a linked list data structure
 *
 */

#include "path_parser.h"
#include "strings.h"
#include "kernelconfig.h"
#include "memory.h"
#include "status.h"
#include "kheap.h"
#include <stdbool.h>

static bool is_drive_format_valid(char *path)
{
    if (memcmp(path, PATHPARSER_DRIVE_VALID_FORMAT, 2) == 0)
    {
        return true;
    }
    return false;
}

static int pathparser_get_drive(char **path)
{
    int drive = char_to_digit(**path);
    if (!is_digit(drive))
    {
        return -EBADPATH;
    }

    /*
    Now we know the drive is valid.  Increment the path string to the next character with &*++(*path)
    If The drive format is valid, ie, contains :/ after the drive number, increment the path by 2 to jump over
    the valid drive format.  I.e, jump over 0:/<path/str now starts here>/
    */
    if (!is_drive_format_valid(&*++(*path)))
    {
        return -EBADPATH;
    }
    *path += 2;
    return drive;
}

static int create_token(PathRoot *root, char *str)
{
    PathToken *token = kmalloc(sizeof(PathToken));
    token->next = NULL;

    char *s = kzalloc(PATHPARSER_MAX_BUF_SIZE * sizeof(char));

    if (!token || !s)
    {
        return -ENOMEM;
    }

    token->str = s;

    // Insert the new token into the linked list.
    PathToken **p = &root->next;
    while (*p)
    {
        p = &(*p)->next;
    }

    *p = token;

    // Copy the tokenized string into memory.
    while (*str)
    {
        *s++ = *str++;
    }

    return 0;
}

static int pathparser_tokenizer(PathRoot *path_root, char *str)
{
    if (strlen(str) <= 0 || strlen(str) > PATHPARSER_MAX_PATH_LEN)
    {
        return 0;
    }

    char *buf = kmalloc(sizeof(char) * PATHPARSER_MAX_BUF_SIZE);

    if (!buf)
    {
        return -ENOMEM;
    }

    char *p_buf = buf;

    while (*str)
    {
        if (*str != '/')
        {
            *p_buf++ = *str++;
            continue;
        }

        *p_buf = 0; // NULL terminate the buffer.
        create_token(path_root, buf);
        p_buf = buf;
        str++;
    }

    /* Flush the buffer and get the last string left in the memory */
    *p_buf = 0;
    create_token(path_root, buf);

    kfree(buf);

    return 0;
}

int pathparser_parse(PathRoot *path_root, char *path, const char *cwd)
{
    char *p_path = path;

    int drive_num = pathparser_get_drive(&p_path);
    if (drive_num < 0)
    {
        return -EBADPATH;
    }

    pathparser_tokenizer(path_root, p_path);

    path_root->drive = drive_num;

    return 0;
}

void pathparser_free(PathRoot *p)
{
    PathToken *node = p->next;
    PathToken *next = NULL;

    while (node)
    {
        next = node->next;
        kfree(node->str);
        kfree(node);
        node = next;
    }
    kfree(p);
}
