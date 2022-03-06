/**
 * @file interrupts.c
 * @author James Carr
 * @brief Interrupt Service Routine Definitions
 * @version 0.1
 * @date 2022-03-06
 * 
 * @copyright Copyright (c) 2022
 * 
 * ISR 0 - Divide By Zero.
 */

#include "stdio.h"

/**
 * @brief ISR 0, Divide by zero definition
 */
void isr_zero()
{
    printf("Error: Divide By Zero\n");
    for (;;)
        ;
}