/**
 * @file keyboard.h
 * @author James Carr
 * @brief Definitions for the keyboard events such as key down and key up events.
 * @version 0.1
 * @date 2022-11-29
 *
 */

#pragma once

struct Scanmap_s
{
    char *character;
};

void handle_keyboard_event();
