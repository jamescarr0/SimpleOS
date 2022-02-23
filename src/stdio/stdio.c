//
// Created by james on 23/02/2022.
//

#include <stddef.h>
#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define FONT_COLOR 15

volatile uint16_t *video = (volatile uint16_t *) 0xB8000;

int terminal_col = 0;
int terminal_row = 0;

size_t strlen(const char *const str) {
    size_t length = 0;

    while (str[length])
        ++length;

    return length;
}

uint16_t create_video_char(const char character, const int color) {
    return (color << 8) | character;
}

void send_to_vga(const int x, const int y, const char character, const int color) {
    video[(y * VGA_WIDTH) + x] = create_video_char(character, color);
}

void putchar(const char character, const int color) {

    if(character == '\n') {
        terminal_row++;
        terminal_col = 0;
        return;
    }

    send_to_vga(terminal_col, terminal_row, character, color);
    terminal_col++;

    if (terminal_col >= VGA_WIDTH) {
        terminal_row++;
        terminal_col = 0;
    }
}

void clear() {
    video = (volatile uint16_t *) 0xB8000;
    for (int y = 0; y < VGA_HEIGHT; ++y) {
        for (int x = 0; x < VGA_WIDTH; ++x)
            send_to_vga(x, y, ' ', 0);
    }
    terminal_col = 0;
    terminal_row = 0;
}

void printf(const char *str) {
    for (int i = 0; i < strlen(str); ++i) {
        putchar(str[i], FONT_COLOR);
    }
}