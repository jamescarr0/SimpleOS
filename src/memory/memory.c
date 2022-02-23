//
// Created by james on 23/02/2022.
//

#include "memory.h"

void *memset(void* ptr, int c, size_t size) {
    char *pC = (char *) ptr;

    for (size_t i = 0; i < size; i++)
        *(pC + i) = c;
    
    return ptr;
}