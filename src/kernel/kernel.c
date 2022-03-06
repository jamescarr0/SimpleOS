/**
 * @file kernel.c
 * @author James Carr
 * @brief Kernel entry, C main() function called from kernerl.asm.
 * @version 0.1
 * @date 19/02/2002
 */

#include "stdio.h"
#include "idt.h"
#include "io.h"

void main() {

    clear();
    printf("Welcome to SimpleOS.\n");
    printf("The simple operating system that currently does nothing :-)\n");

    // Initiliase the IDT
    idt_init();

    io_write_byte(0x60, 0xAB);  // Dummy code to test write_byte driver.

    // int a = 10*2/0; // Dummy code to test IDT & ISR0. Division by zero.
}