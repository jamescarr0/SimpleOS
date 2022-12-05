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
#include "time/tick.h"

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

/**
 * @brief 0x20 : System Tick. 18.222 times per second.
 * http://www.osdever.net/bkerndev/Docs/pit.htm
 *
 * By default, the timer fires 18.222 times
 *  per second. Why 18.222Hz? Some engineer at IBM must've
 *  been smoking something funky
 * 
 */
void int_handler_20(void) {
    handle_tick();
    PIC_send_EOI(IRQ_TIMER);
}

// 0x21 : Keyboard Interrupt handler
void int_handler_21(void)
{
    // Key release info: https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html
    handle_keyboard_event();
    PIC_send_EOI(IRQ_KEYBOARD);
}
