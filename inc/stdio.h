/**
 * @file stdio.h
 * @author James Carr
 * @brief Kernel declerations for standard input and output
 * @version 0.1
 * @date 2022-03-07
 * 
 * Kernel definitions for standard input and output.
 */

#ifndef SIMPLEOS_STDIO_H
#define SIMPLEOS_STDIO_H

#include <stdint.h>
#include <stddef.h>

/**
 * Setup the terminal
 */

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define FONT_COLOR 15

typedef struct Terminal_s{
    uint8_t col_pos;
    uint8_t row_pos;
    volatile uint16_t *framebuffer;
} Terminal;

/**
 * @brief Clear the terminal and reset the terminal cursor x and y position to 0, 0.
 * 
 */
void clear(void);

/**
 * @brief C Style print function.
 * @param str String to print to stdout (console)
 */
void print(const char *const str);

#endif //SIMPLEOS_STDIO_H
