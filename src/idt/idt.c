/**
 * @file idt.c
 * @author James Carr
 * @date 02/03/2022
 * @brief Source code for implementing the Interrupt Descriptor Table.
 * 
 * Initiliase and implements the IDR, IDTR and Interrupt service routines.
 * IRQ1 - refers to array[1]
 * IRQ2 - refers to array[2]
 * .
 * .
 * .
 * IRQ15 - refers to array[15]
 * 
 */

#include <stdint.h>

#include "stdio.h"
#include "idt.h"
#include "memory.h"
#include "kernelconfig.h"

idt_entry_t idt32desc_table[SIMPLEOS_MAX_INTERRUPTS];
idtr_t idtr_desc;

// IRQ0
void isr_zero() {
    printf("Error: Divide By Zero\n");
    for(;;);
}

// Create and initilaise the IDT and IDTR
void idt_init() {
    memset(idt32desc_table, 0, sizeof(idt32desc_table));

    idtr_desc.size = sizeof(idt32desc_table) - 1;
    idtr_desc.offset = (uint32_t) idt32desc_table;

    idt_set(0, isr_zero);   // Interrupt 0 - Divide by zero error

    // Load idt table
    lidt(&idtr_desc);
}

// Create Interrupt Service Routines
void idt_set(const int interrupt_number, const void *const address) {
    idt_entry_t *descriptor = &idt32desc_table[interrupt_number];

    descriptor->offset_1 = (uint32_t) address;
    descriptor->selector = KERNEL_CODE_SELECTOR;
    descriptor->zero = 0;
    descriptor->type_attr = 0xEE;   // Set Gate, Storage, RING & IRQ Number
    descriptor->offset_2 = (uint32_t) address >> 16;
}
