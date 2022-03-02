/**
 * @file memory.c
 * @author James Carr
 * @date 23/02/2022
 * @brief Source code for kernel memory function implementations.
 * 
 * The header file contains implementations for memory funcitons used by the kernel
 * 
 */

#include "memory.h"

/**
 * Sets a block of memory of n bytes with the specified value.
 *
 * @param ptr Pointer to the starting address of the memory block to fill.
 * @param c Value to fill the memory block with.
 * @param size Number of bytes to set.
 * @return void pointer to the starting address.
 */
void *memset(void* ptr, int c, size_t size) {
    char *pC = (char *) ptr;

    for (size_t i = 0; i < size; i++)
        pC[i] = c;
    
    return ptr;
}