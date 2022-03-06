/**
 * @file memory.h
 * @author James Carr
 * @brief Declerations for memory related tasks used by ther kernel
 * @version 0.1
 * @date 2022-02-23
 * 
 */


#ifndef SIMPLEOS_MEMORY_H
#define SIMPLEOS_MEMORY_H

#include <stddef.h>

/**
 * Sets a block of memory of n bytes with the specified value.
 *
 * @param ptr Pointer to the starting address of the memory block to fill.
 * @param c Value to fill the memory block with.
 * @param size Number of bytes to set.
 * @return void pointer to the starting address.
 */
void *memset(void *ptr, int c, size_t size);

#endif // SIMPLEOS_MEMORY_H
