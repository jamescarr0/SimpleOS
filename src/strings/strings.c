/**
 * @file Source code to implement string related functions.
 * @date 22/02/2022
 * **Author:** James Carr
 * ## Role
 * Provides the kernel with string and character related functions.
 */

#include <stddef.h>

/**
 * Iterate and count the length of a NULL terminated string.
 *
 * @param str A NULL terminated string.
 * @return the length of the string
 */

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