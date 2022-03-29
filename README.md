# Simple OS
## An operating system written in C and built from scratch.

SimpleOS is a 32-bit operating system for X86.

<hr>

### Work in progress

:x: Create a disk driver in C to read from the hard disk 

<hr>

### Current status:

:heavy_check_mark: Real mode 16 bit bootloader

:heavy_check_mark: Switch to 32 bit protected mode.

:heavy_check_mark: Abstracted to C.  Load kernel into memory and call main() (kernel.c)

:heavy_check_mark: Implement and load the global descriptor table.

:heavy_check_mark: Implement and load the Interrupt Descriptor table, created a working keyboard interrupt.

:heavy_check_mark: Enabled interrupts.

:heavy_check_mark: Implement a print function to send character bytes to video memory for output to screen.

:heavy_check_mark: Implement the heap and memory allocation functions kmalloc, kzalloc and kfree.

:heavy_check_mark: Implement paging using 4kb pages.
