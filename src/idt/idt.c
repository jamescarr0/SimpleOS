/**
 * @file idt.c
 * @author James Carr
 * @date 02/03/2022
 * @brief Source code for implementing the Interrupt Descriptor Table.
 *
 * Initiliase and implements the IDR, IDTR and Interrupt service routines.
 *
 */

#include <stdint.h>

#include "stdio.h"
#include "idt.h"
#include "memory.h"
#include "kernelconfig.h"
#include "interrupts.h"

/**
 * @brief Interrupt descriptor vector
 * IRQ1 - refers to array[1]
 * IRQ2 - refers to array[2]
 * .
 * .
 * .
 * IRQ15 - refers to array[15]
 */
idt_entry_t idt32desc_table[SIMPLEOS_MAX_INTERRUPTS]; // The actual interrupt descriptor table.

idtr_t idtr_desc;                                     //  Interrupt descriptor table register instance.

// Create and initilaise the IDT and IDTR
void idt_init()
{
    // Clear memory and initiliase array (IDT vector) with zeros.
    memset(idt32desc_table, 0, sizeof(idt32desc_table));

    idtr_desc.size = sizeof(idt32desc_table) - 1;
    idtr_desc.offset = (uint32_t)idt32desc_table;

    /* Attributes For a 32 bit Gate Descriptor.
     * Bit 47       : Present bit - Must be set to 1 for descriptor to be valid.
     * Bit 46-45    : DPL (privilege/ring level)
     * Bit 44       : Unused
     * Bit 43-40    : Gate Type
     */
    uint8_t attributes = PRESENT_BIT_SET << 7 | IDT_RING_3 << 6 | UNUSED << 4 | IDT_INTERRUPT_GATE;

    // Set Interrupt service routines.
    idt_set(0, isr_zero, attributes); // Interrupt 0 - Divide by zero error

    // Load idt table
    lidt(&idtr_desc);
}

// Create Interrupt Service Routines
void idt_set(const int interrupt_number, const void *const isr_address, uint8_t attributes)
{
    idt_entry_t *descriptor = &idt32desc_table[interrupt_number];
    descriptor->offset_1 = (uint32_t)isr_address;
    descriptor->selector = KERNEL_CODE_SELECTOR;
    descriptor->zero = 0;
    descriptor->type_attr = attributes;
    descriptor->offset_2 = (uint32_t)isr_address >> 16;
}
