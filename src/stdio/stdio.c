/**
 * @page Implements standard input and output streams.
 * @date 23/02/2022
 * **Author:** James Carr
 * ## Role
 * To establish functions providing input and output capabilities.
 */

#include <stdint.h>
#include "strings.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define FONT_COLOR 15

static volatile uint16_t *video_memory = (volatile uint16_t *) 0xB8000;

int terminal_col = 0;
int terminal_row = 0;

/**
 * Text video_memory mode memory requires two bytes for every character on
 * the screen.
 *
 * @param character ASCII character
 * @param color Color code to set foreground color of ASCII character
 * @return 16-bit (two-byte) value that can be sent to video memory.
 */
static uint16_t create_video_char(const char character, const int color) {
    return (color << 8) | character;
}


/**
 * Sends the unit16_t (two byte character/color combination) directly to video
 * memory.
 *
 * @param x X position of the character to be displayed on stdout
 * @param y Y position of the character to be displayed on stdout
 * @param character The ASCII character to display
 * @param color The foreground color of the ASCII character
 */
static void send_to_video_memory(const int x, const int y, const char character, const int color) {
    video_memory[(y * VGA_WIDTH) + x] = create_video_char(character, color);
}


/**
 * Responsible for tracking the characters being sent to video memory and to identify
 * escape sequences in the string such as newline.
 *
 * @param character
 * @param color
 */
static void putchar(const char character, const int color) {
    if(character == '\n') {
        terminal_row++;
        terminal_col = 0;
        return;
    }

    send_to_video_memory(terminal_col, terminal_row, character, color);
    terminal_col++;

    if (terminal_col >= VGA_WIDTH) {
        terminal_row++;
        terminal_col = 0;
    }
}


/**
 * Clear the terminal and reset the terminal cursor x and y position to 0, 0.
 */
void clear(void) {
    video_memory = (volatile uint16_t *) 0xB8000;
    for (int y = 0; y < VGA_HEIGHT; ++y) {
        for (int x = 0; x < VGA_WIDTH; ++x)
            send_to_video_memory(x, y, ' ', 0);
    }
    terminal_col = 0;
    terminal_row = 0;
}


/**
 * Write a NULL terminated string to standard output.
 *
 * @param str NULL terminated string to send to stdout.
 */
void printf(const char *const str) {
    for (size_t i = 0; i < strlen(str); ++i) {
        putchar(str[i], FONT_COLOR);
    }
}