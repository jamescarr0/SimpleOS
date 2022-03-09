/**
 * @file heap.h
 * @author James Carr
 * @brief Create and manage heap memory
 * @version 0.1
 * @date 2022-03-08
 *
 *
 */

#ifndef SIMPLEOS_HEAP_H
#define SIMPLEOS_HEAP_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "kernelconfig.h"

// Heap Block Table defines
#define HEAP_BLOCK_TABLE_ENTRY_TAKEN 0x01
#define HEAP_BLOCK_TABLE_ENTRY_FREE 0x00

// Bit masks for the heap blocks in the heap block table
// MSB represents the block has another block next to it.
// MSB-1 represents if the block is free to use.
#define HEAP_BLOCK_HAS_NEXT 0b10000000
#define HEAP_BLOCK_IS_FIRST 0b01000000

typedef unsigned char HBT_ENTRY_t;

/**
 * @brief Entry based heap table.
 *
 * Table contains a finite (total_entries) number of block entries
 */
typedef struct
{
    HBT_ENTRY_t *entries; // Pointer to heap block entries
    size_t total_entries; // Total Number of entries.
} heap_table_t;

/**
 * @brief The heap.
 *
 * Contains the a pointer to the heap table and the starting address
 * of the heap.
 */
typedef struct
{
    heap_table_t *heap_table; // Pointer to heap table.
    void *start_address;      // Start address of the heap
} heap_t;

/**
 * @brief Initialises and creates a new heap.
 *
 * @param heap Uninitialised heap structrue
 * @param heap_start Starting address of heap
 * @param heap_end End address of heap
 * @param table Heap table pointing to the heap entries
 * @return int
 */
int heap_create(heap_t *heap, void *heap_start_addr, void *heap_end_addr, heap_table_t *table);

/**
 * @brief 
 * 
 * @param heap 
 * @param ptr 
 */
void heap_free(heap_t *heap, void *ptr);

/**
 * @brief 
 * 
 * @param heap 
 * @param size 
 * @return void* 
 */
void *heap_malloc(heap_t *heap, size_t size);

#endif
