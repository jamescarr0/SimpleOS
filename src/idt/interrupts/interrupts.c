/**
 * @file interrupts.c
 * @author James Carr
 * @brief Interrupt Service Routine Definitions
 * @version 0.1
 * @date 2022-03-06
 *
 *
 * ISR 0    - Divide By Zero.
 * ISR 33   - IRQ[0x21] - remapped(irq1) Keyboard Interrupt 
 *
 */

#include "stdio.h"
#include "io.h"
#include "interrupts.h"
#include "pic.h"
#include "input/keyboard.h"

// Default interrupt handler when no ISR is assigned to a IRQ
void no_interrupt_handler(void)
{
    outb(0x20, 0x20);
}

// ISR 0, Divide by zero definition
void isr_zero()
{
    print("Error: Divide By Zero\n", red);
    for (;;)
        ;
}

// 0x21 : Keyboard Interrupt handler
void int_handler_21(void)
{
    // Key release info: https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html

    // uint8_t key_code = insb(0x60); // Read keypress from buffer

    // char *c = scanmap[key_code].character;  // Get key from mapping.
    // if(key_code < 0x80) print(c, green);
    // else if (key_code > 128) { /* A key has been released, KEY UP event */ } 

    handle_keyboard_event();
    PIC_send_EOI(IRQ_KEYBOARD);
}
