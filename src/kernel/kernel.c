/**
 * @file kernel.c
 * @author James Carr
 * @brief Kernel entry, main() called from kernel.asm
 * @version 0.1
 * @date 19/02/2002
 */

#include "stdio.h"
#include "idt.h"
#include "io.h"
#include "kheap.h"
#include "interrupts.h"

void main() {

    clear();
    printf("Welcome to SimpleOS.\n");

    // Initialise the heap.
    kheap_init();

    // Initialiase the IDT.
    idt_init();

    // Enable interrupts.
    enable_interrupts();
    
}