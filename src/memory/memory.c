/**
 * @file memory.c
 * @author James Carr
 * @date 23/02/2022
 * @brief Source code for kernel memory function implementations.
 *
 * Implementations for memory related tasks used by the kernel
 *
 */

#include "memory.h"

/* Implementation of the C memset function */
void *memset(void *ptr, int c, size_t size)
{
    char *pC = (char *)ptr;

    for (size_t i = 0; i < size; i++)
        pC[i] = c;

    return ptr;
}