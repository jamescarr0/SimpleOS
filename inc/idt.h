/**
 * @file Interrupt Descriptor Table header.
 * @date 02/03/2022
 * **Author:** James Carr
 * ## Role
 * Create IDT and IDTR data structure declerations.
 * The IDT tells the CPU where the Interrupt Service routines are located.
 */

#ifndef SIMPLEOS_IDT_H
#define SIMPLEOS_IDT_H

#include <stdint.h>

typedef struct
{
    uint16_t offset_1;          // Offset bits 0...15
    uint16_t selector;          // Code segment selector in GDT
    uint8_t zero;               // Unused - Set to 0
    uint8_t type_attr;          // 4 bit Gate Type,
                                // 1 bit Storage Segment
                                // 2 bit Descriptor Privilege Level
                                // Present (IRQ No.) Set to Zero for Unused IRQ.
    uint16_t offset_2;          // Offset 16...31
} __attribute__((packed)) idt_entry_t;

typedef struct
{
    uint16_t size;
    uint32_t offset;
} __attribute__((packed)) idtr_t;


extern void idt_load(idtr_t *ptr);

void idt_init();

void idt_set(const int IRQ_number, const void *const address);

#endif // SIMPLEOS_IDT_H