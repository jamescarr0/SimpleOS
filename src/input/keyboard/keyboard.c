/**
 * @file keyboard.c
 * @author James Carr
 * @brief Handles the keyboard events such as key down and key up events.
 * @version 0.1
 * @date 2022-11-29
 *
 */

#include "stdio.h"
#include "input/keyboard.h"

extern const struct Scanmap_s kbd_scanmap[];

void handle_keyboard_event()
{
    uint8_t key_code = insb(0x60); // Read keypress from buffer

    char *c = kbd_scanmap[key_code].character;  // Get key from mapping.

    if(key_code < 0x80) print(c, green);
    else if (key_code > 128) { /* A key has been released, KEY UP event */ } 
}