//
// Created by james on 23/02/2022.
//


#ifndef SIMPLEOS_STDIO_H
#define SIMPLEOS_STDIO_H

#include <stdint.h>
#include <stddef.h>


uint16_t create_video_char(char character, int color);
/* Text video_memory mode memory requires two bytes for every character on
 * the screen.
 *
 * https://wiki.osdev.org/Printing_to_Screen
 *
 * <ASCII CODE byte> <COLOR attribute byte>
 *
 * Parameters:
 * char character : ASCII character
 * int color: Color code
 *
 * Returns:
 * 16 bit (two-byte) value that can be sent straight to video memory in the
 * correct little endian format.
 * */

void send_to_video_memory(int x, int y, char character, int color);
/* Sends the unit16_t (two byte character/color combination) directly to video
 * memory and inserts character at the x, and y location of the terminal.
 *
 * Parameters:
 * int x: X cursor position.
 * int y: Y cursor position.
 * char character: ASCII character
 * int color: foreground color code to display ascii character.
 *
 * */

void putchar(char, int);
/* Putchar is responsible for tracking the characters being sent to video
 * memory.  The function checks each character for escape sequences and will
 * begin a new row when a character reaches the column width (VGA_WIDTH).
 */

void clear();
/* Clears the terminal and resets the terminal cursor position, x and y, to
 * 0.
 */

void printf(char *);
/* Write string to terminal (stdout) */

#endif //SIMPLEOS_STDIO_H
