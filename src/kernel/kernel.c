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
    
}