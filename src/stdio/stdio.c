//
// Created by james on 23/02/2022.
//

#include <stdint.h>
#include "strings.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define FONT_COLOR 15

static volatile uint16_t *video_memory = (volatile uint16_t *) 0xB8000;

int terminal_col = 0;
int terminal_row = 0;

static uint16_t create_video_char(const char character, const int color) {
    /* Video memory requires two bytes for every character on screen
     * An ascii byte, and a colour code byte.
     *
     * Since x86 is little endian, bytes must be reversed.
     * The colour code is shifted left one byte and then a bitwise OR mask is
     * applied using the ASCII character byte.
     * */
    return (color << 8) | character;
}

static void send_to_video_memory(const int x, const int y, const char character, const int color) {
    /* Sends the character and color two byte value directly to video memory
     * at the x and y coordinates of the terminal.
     *
     * video_memory[cursor_position]
     *
     * */
    video_memory[(y * VGA_WIDTH) + x] = create_video_char(character, color);
}

static void putchar(const char character, const int color) {
    /* Keep track of the location of characters being sent to video memory.
     * Detects when to wrap text to the next line and checks for escape
     * sequences.
     * */
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

void clear() {
    /* Clears the terminal view of text and resets cursor position.
     *
     * Clear contents of video memory by placing white space chars the same
     * colour as the terminal background.*/

    video_memory = (volatile uint16_t *) 0xB8000;
    for (int y = 0; y < VGA_HEIGHT; ++y) {
        for (int x = 0; x < VGA_WIDTH; ++x)
            send_to_video_memory(x, y, ' ', 0);
    }
    terminal_col = 0;
    terminal_row = 0;
}

void printf(const char *const str) {
    /* Printf! What more can we say :-) Happy days. */
    for (int i = 0; i < strlen(str); ++i) {
        putchar(str[i], FONT_COLOR);
    }
}