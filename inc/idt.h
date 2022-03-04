/**
 * @file idt.h
 * @author James Carr
 * @brief IDT and IDTR type and function decleartions
 * @version 0.1
 * @date 02/03/2022
 * 
 */

#ifndef SIMPLEOS_IDT_H
#define SIMPLEOS_IDT_H

#include <stdint.h>

/**
 * @brief 
 * 
 */
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

/**
 * @brief 
 * 
 */
typedef struct
{
    uint16_t size;
    uint32_t offset;
} __attribute__((packed)) idtr_t;

/**
 * @brief 
 * 
 * @param pIDTR 
 */
static inline void lidt(idtr_t const *const pIDTR)
{  
    asm ( "lidt %0" : : "m"(*pIDTR) );
}

/**
 * @brief 
 * 
 */
void idt_init();

/**
 * @brief 
 * 
 * @param interrupt_number 
 * @param address 
 */
void idt_set(const int interrupt_number, const void *const address);

#endif // SIMPLEOS_IDT_H