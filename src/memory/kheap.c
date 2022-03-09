/**
 * @file kheap.c
 * @author James Carr
 * @brief
 * @version 0.1
 * @date 2022-03-08
 *
 *
 */

#include "kheap.h"
#include "heap.h"
#include "stdio.h"

heap_t kernel_heap;
heap_table_t kernel_heap_table;

// Create and initialise a kernel heap.
void kheap_init()
{
    // Total Number of block entries the heap will manage. 
    int total_table_entries = KERNEL_HEAP_SIZE_BYTES / KERNEL_HEAP_BLOCK_SIZE;

    // Initialise the heap table with a starting heap address and
    // the total number of entries the table will manage.
    kernel_heap_table.entries = (HBT_ENTRY_t *)KERNEL_HEAP_TABLE_ADDRESS;
    kernel_heap_table.total_entries = total_table_entries;

    // End of the heap.
    int *heap_end = (void *) KERNEL_HEAP_ADDRESS + KERNEL_HEAP_SIZE_BYTES;

    int res = heap_create(&kernel_heap, (void *) KERNEL_HEAP_ADDRESS, heap_end, &kernel_heap_table);
    if (res < 0) 
    {
        printf("Kernel Panic TODO: Failed to init and create heap!\n");
    }
}

// Allocate number of bytes for the kernel heap.
void *kmalloc(size_t size)
{
    return heap_malloc(&kernel_heap, size);
}

// Free previously allocated kernel memory.
void kfree(void *ptr)
{
    heap_free(&kernel_heap, ptr);
}
