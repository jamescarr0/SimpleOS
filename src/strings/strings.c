/**
 * @file Source code to implement string related functions.
 * @date 22/02/2022
 * **Author:** James Carr
 * ## Role
 * Provides the kernel with string and character related functions.
 */

#include <stddef.h>

size_t strlen(const char *const str) {
    /* Iterate a string and increment the length counter
     * String must be NULL terminated.
     *
     * Returns:
     * Length of NULL terminated string
     */
    size_t length = 0;
    char *p = str;

    while (*p++)
        length++;

    return length;
}