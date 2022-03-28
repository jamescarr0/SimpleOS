/**
 * @file kernel.c
 * @author James Carr
 * @brief Kernel directory, main() called from kernel.asm
 * @version 0.1
 * @date 19/02/2002
 */

#include "stdio.h"
#include "idt.h"
#include "io.h"
#include "kheap.h"
#include "interrupts.h"
#include "paging.h"

void main() {

    clear();
    printf("Welcome to SimpleOS.\n");

    // Initialise the heap.
    kheap_init();

    // Initialize the IDT.
    idt_init();

    // Init paging
    uint8_t page_flags = PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL;

    PagingDir_4gb *page_dir = init_4gb_page_dir(page_flags);

    // Switch to the kernel paging chunk of memory.
    paging_switch(paging_get_dir(page_dir));

    // Enable paging
    enable_paging();

    // Enable interrupts.
    enable_interrupts();
    
}