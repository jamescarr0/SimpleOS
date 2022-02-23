/**
 * @page kernel header for stdio function prototypes.
 * @date 23/02/2022
 * **Author:** James Carr
 * ## Role.
 * Provides standard input and output function definitions for the kernel.
 */

#ifndef SIMPLEOS_STDIO_H
#define SIMPLEOS_STDIO_H

#include <stdint.h>
#include <stddef.h>

uint16_t create_video_char(char character, int color);

void send_to_video_memory(int x, int y, char character, int color);

void putchar(char character, int color);

void clear(void);

void printf(char *str);

#endif //SIMPLEOS_STDIO_H
