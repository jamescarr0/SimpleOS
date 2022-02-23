//
// Created by james on 23/02/2022.
//

#include <stddef.h>

size_t strlen(const char *const str) {
    /* Iterate a string and increment the length counter
     * String must be NULL terminated.
     *
     * Returns:
     * Length of NULL terminated string
     */
    size_t length = 0;

    while (str[length])
        ++length;

    return length;
}