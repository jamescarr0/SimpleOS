//
// Created by james on 23/02/2022.
//


#ifndef SIMPLEOS_STDIO_H
#define SIMPLEOS_STDIO_H

#include <stdint.h>
#include <stddef.h>

size_t strlen(char*);
uint16_t create_video_char(char, int);
void send_to_vga(int, int, char, int);
void putchar(char, int);
void clear();
void printf(char *);

#endif //SIMPLEOS_STDIO_H
