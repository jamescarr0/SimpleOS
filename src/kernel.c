//
// Created by james on 20/02/2022.
//

#include "kernel.h"

#define TEXT_COLOR 2
#define TEXT_CLEAR 0

void kernel_main() {

    /*  Quick dirty code for clearing and printing to the screen */

    // Pointer to the text screen video memory
    // Text mode memory takes two bytes per character.
    // byte1 <character> : byte2 <colour>
    volatile char* video = (volatile char*) 0xB8000;
    int scr_xy = 80*25;
    int ctr = 0;
    while(ctr < scr_xy) {
        *video++ =  *" ";
        *video++ = TEXT_CLEAR;
        ctr++;
    }

    // Screen clear, reset video address.
    video = (volatile char*) 0xB8000;

    char *msg1 = "Welcome to SimpleOS!";
    char *msg2 = "A simple operating system written from scratch";

    int string_length = 0;
    while(*msg1 != '\0') {
        *video++ = *msg1++;
        *video++ = TEXT_COLOR;
        ++string_length;
    }

    int newline = 80 - string_length;
    for (int i = 0; i < newline; ++i) {
        *video++ = *" ";
        *video++ = TEXT_COLOR;
    }

    while(*msg2 != '\0') {
        *video++ = *msg2++;
        *video++ = TEXT_COLOR;
    }

    while(1);
}