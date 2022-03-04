/**
 * @file io.h
 * @author James Carr
 * @brief Define input output functions for writing and reading data from ports.
 * @version 0.1
 * @date 2022-03-03
 *
 * ASM code now replaced with static inline assembly, example code from
 * OS Dev.
 *
 * io.asm does work; file kept as a backup incase gcc compilation produces
 * unacceptable results.
 *
 * " What follows is a collection of inline assembly functions so common
 * that they should be useful to most OS developers using GCC ""
 * https://wiki.osdev.org/Inline_Assembly/Examples
 *
 */

#ifndef SIMPLEOS_IO_H
#define SIMPLEOS_IO_H

#include <stdint.h>

/******************** ASM Funcs begin ********************
 *
 * Working as should.  Replaced with C inline functions/assembly.
 * If gcc introduces compilation bugs or strange asm syntax
 * revert back to working asm routines in found io.asm and
 * declared below
 */

// unsigned char io_read_byte(unsigned short port);

// unsigned short io_read_word(unsigned short port);

// void io_write_byte(unsigned short port, unsigned data);

// void io_write_word(unsigned short port, unsigned data);

/******************** ASM Funcs end ********************/

/* Inline Assembly Functions */

/**
 * @brief Write a byte to the specified I/O port
 *
 * @param port The I/O port to write a byte to.
 * @param val The value (byte) to be sent to the I/O port.
 */
static inline void io_write_byte(uint16_t port, uint8_t val)
{
    __asm__ volatile("out %0, %1"
                     :
                     : "a"(val), "Nd"(port));
}

/**
 * @brief Write a word to the specified I/O port
 *
 * @param port The I/O port to write a word to.
 * @param val The value (word) to be sent to the I/O port.
 */
static inline void io_write_word(uint16_t port, uint16_t val)
{
    __asm__ volatile("out %0, %1"
                     :
                     : "a"(val), "Nd"(port));
}

/**
 * @brief Write a long 32-bit value to the specified I/O port
 *
 * @param val The long value (32-bit) to be sent to the I/O port.
 * @param port The I/O port to write a long value to.
 */
static inline void io_write_long(uint16_t port, uint32_t val)
{
    __asm__ volatile("out %0, %1"
                     :
                     : "a"(val), "Nd"(port));
}

/**
 * @brief Read a byte from the specified I/O port
 *
 * @param port The I/O port to read a byte from.
 * @return uint8_t - A byte from the I/O port.
 */
static inline uint8_t io_read_byte(uint16_t port)
{
    uint8_t ret;
    __asm__ volatile("inb %1, %0"
                     : "=a"(ret)
                     : "Nd"(port));
    return ret;
}

/**
 * @brief Read a word from the specified I/O port
 *
 * @param port The I/O port to read a word from/
 * @return uint16_t - A word from the I/O port.
 */
static inline uint16_t io_read_word(uint16_t port)
{
    uint16_t ret;
    __asm__ volatile("inw %1, %0"
                     : "=a"(ret)
                     : "Nd"(port));
    return ret;
}

/**
 * @brief Read a long 32-bit value from the specified I/O port
 *
 * @param port The I/O port to read a long word from.
 * @return uint32_t - A long (32-bit) word from the I/O port.
 */
static inline uint32_t io_read_long(uint16_t port)
{
    uint32_t ret;
    __asm__ volatile("inl %1, %0"
                     : "=a"(ret)
                     : "Nd"(port));
    return ret;
}

#endif