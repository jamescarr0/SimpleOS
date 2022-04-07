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
#include "disk.h"
#include "path_parser.h"
#include "disk_stream.h"

int main() {

    clear();
    print("Welcome to SimpleOS.\n");

    // Initialise the heap.
    kheap_init();

    // Search and initialise disks, NOTE: OS currently uses the primary master only.
    disks_init();

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

    // Driver code for debugging reading bytes in memory.
    DiskStream *stream = disk_stream_new(0);
    disk_stream_seek(stream, 0);
    unsigned char c[1501] = {0};
    disk_stream_read(stream, &c, 1500);

    while(1);

    return 0;
    
}