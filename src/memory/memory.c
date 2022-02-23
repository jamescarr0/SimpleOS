/**
 * @page Source code for memory function definitions
 * @date 23/02/2022
 * **Author:** James Carr
 * ## Role.
 * To provide the kernel with functions to work with memory.
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
        *(pC + i) = c;
    
    return ptr;
}