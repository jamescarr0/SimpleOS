/**
 * @file stdio.c
 * @author James Carr
 * @brief Function definitions for standard input output.
 * @version 0.1
 * @date 2022-23-02
 *
 * Definitions for standard input ouput.
 */

#include <stdint.h>
#include "strings.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define FONT_COLOR 15

int terminal_col = 0; // Terminal columns
int terminal_row = 0; // Terminal row

static volatile uint16_t *video_memory = (volatile uint16_t *)0xB8000; // Text video memory.

/* Text video memory requires two bytes per character.  An ASCII byte, and an attribute
byte, which is the colour of the character to be sent to video memory.
X86 is little endian so the bytes need to be converted (reversed) accordingly with
a bitshift left and biwide or
 */
static uint16_t create_video_char(const char character, const int color)
{
    return (color << 8) | character; // Convert to little endianess. Swap bytes.
}

/* Inserts the 'two byte' text video character into video memory at location x, y */
static void send_to_video_memory(const int x, const int y, const char character, const int color)
{
    video_memory[(y * VGA_WIDTH) + x] = create_video_char(character, color);
}

/* Update the terminal cursor position and send the character to be inserted into video memory to the
video memory helper function 'send_to_video_memory' */
static void putchar(const char character, const int color)
{
    if (character == '\n') // Increment the terminal row position when reading a newline.
    {
        terminal_row++;
        terminal_col = 0;
        return;
    }

    // Send the char to video memory.
    send_to_video_memory(terminal_col, terminal_row, character, color);
    terminal_col++;

    // Wrap text to a newline when the end of the terminal is reached.
    if (terminal_col >= VGA_WIDTH)
    {
        terminal_row++;
        terminal_col = 0;
    }
}

/* Clears the terminal screen by iterating the video memory vector and inserting
 * white space
 */
void clear(void)
{
    video_memory = (volatile uint16_t *)0xB8000;
    for (int y = 0; y < VGA_HEIGHT; ++y)
    {
        for (int x = 0; x < VGA_WIDTH; ++x)
            send_to_video_memory(x, y, ' ', 0);
    }
    terminal_col = 0;
    terminal_row = 0;
}

/* C Style printf function for printing characters to the terminal */
void printf(const char *const str)
{
    for (size_t i = 0; i < strlen(str); ++i)
    {
        putchar(str[i], FONT_COLOR);
    }
}