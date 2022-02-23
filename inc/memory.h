/**
 * @page kernel header for memory function prototypes.
 * @date 23/02/2022
 * **Author:** James Carr
 * ## Role.
 * Provides memory function prototypes for the memory operations.
 */

#ifndef SIMPLEOS_MEMORY_H
#define SIMPLEOS_MEMORY_H

#include <stddef.h>

void *memset(void* ptr, int c, size_t size);

#endif //SIMPLEOS_MEMORY_H
