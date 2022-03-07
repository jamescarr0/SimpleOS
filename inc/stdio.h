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
 * @brief Text video_memory mode memory requires two bytes for every character on
 * the screen.
 *
 * @param character ASCII character
 * @param color Color code to set foreground color of ASCII character
 * @return 16-bit (two-byte) value that can be sent to video memory.
 */
uint16_t create_video_char(char character, int color);

/**
 * @brief Sends the unit16_t (two byte character/color combination) directly to video
 * memory.
 *
 * @param x X position of the character to be displayed on stdout
 * @param y Y position of the character to be displayed on stdout
 * @param character The ASCII character to display
 * @param color The foreground color of the ASCII character
 */
void send_to_video_memory(int x, int y, char character, int color);

/**
 * @brief Responsible for tracking the characters being sent to video memory and to identify
 * escape sequences in the string such as newline.
 *
 * @param character
 * @param color
 */
void putchar(char character, int color);

/**
 * @brief Clear the terminal and reset the terminal cursor x and y position to 0, 0.
 * 
 */
void clear(void);

/**
 * @brief C Style print function.
 * 
 * @param str String to print to stdout (console)
 */
void printf(char *str);

#endif //SIMPLEOS_STDIO_H
