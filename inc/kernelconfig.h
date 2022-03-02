/**
 * @file kernelconfig.h
 * @author James Carr
 * @date 02/03/2022
 * @brief Configuration settings for SimpleOS Kernel.
 * 
 */

#ifndef SIMPLEOS_KERNELCONFIG_H
#define SIMPLEOS_KERNELCONFIG_H

#define SIMPLEOS_MAX_INTERRUPTS 512
#define KERNEL_CODE_SELECTOR 0x8   // CODE_SEG in kernel.asm
#define KERNEL_DATA_SELECTOR 0x10   // DATA_SEG in kernel.asm

#endif
