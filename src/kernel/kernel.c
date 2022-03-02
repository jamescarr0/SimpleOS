/**
 * @file Kernel Entry: Main() function.
 * @date 19/02/2022
 * **Author:** James Carr
 * ## Role
 * Kernel entry point, main() function called from the assembly bootloader.
 */

#include "stdio.h"
#include "idt.h"

extern void irq0_test();

void main() {

    clear();
    printf("Welcome to SimpleOS.\n");
    printf("The simple operating system that currently does nothing :-)\n");

    // Initiliase the IDT
    idt_init();

    irq0_test();
}