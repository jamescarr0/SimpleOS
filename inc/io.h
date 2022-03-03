/**
 * @file io.h
 * @author James Carr
 * @brief 
 * @version 0.1
 * @date 2022-03-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SIMPLEOS_IO_H
#define SIMPLEOS_IO_H

unsigned char io_read_byte(unsigned const short port);

unsigned short io_read_word(unsigned const short port);

void io_write_byte(unsigned const short port, unsigned char data);

void io_write_word(unsigned const short port, unsigned short data);

#endif