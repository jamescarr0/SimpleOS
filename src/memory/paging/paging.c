//
// Created by James Carr on 24/03/2022.
//

#include "paging.h"
#include "kheap.h"
#include "status.h"

static uint32_t *current_dir = NULL;

// Create & initialise paging directory.
PagingDir_4gb *init_4gb_page_dir(uint8_t flags)
{
    uint32_t *dir = kzalloc(sizeof (uint32_t) * PAGING_TOTAL_ENTRIES_PER_TABLE);

    int offset = 0;

    // Create a paging table for each of the 1024 directory entries.
    for (int i = 0; i < PAGING_TOTAL_ENTRIES_PER_TABLE; ++i) {
        uint32_t *entry = kzalloc(sizeof (uint32_t) * PAGING_TOTAL_ENTRIES_PER_TABLE);

        for (int j = 0; j < PAGING_TOTAL_ENTRIES_PER_TABLE; ++j) {
            entry[j] = (offset + (j * PAGING_PAGE_SIZE)) | flags;
        }

        offset += (PAGING_TOTAL_ENTRIES_PER_TABLE * 4096);

        dir[i] = (uint32_t) entry | flags | PAGING_IS_WRITEABLE;
    }

    PagingDir_4gb *chunk = kzalloc(sizeof (PagingDir_4gb));
    chunk->directory = dir;

    return chunk;
}

void paging_switch(uint32_t *directory)
{
    paging_load_dir(directory);
    current_dir = directory;
}

uint32_t *paging_get_dir(PagingDir_4gb *page_dir)
{
    return page_dir->directory;
}

// Paging must work on 4096 aligned boundaries.
bool paging_is_aligned(void *addr)
{
    return ( (uint32_t) addr % PAGING_PAGE_SIZE ) == 0;
}

// Resolve a virtual address to a directory index and a table index.
int paging_get_indexes(void *virtual_addr, uint32_t *dir_index, uint32_t *table_index)
{
    int res = 0;
    if(!paging_is_aligned(virtual_addr))
    {
        return -EINVARG;
    }

    // Eg: Virtual_address = 0x405000
    // virtual address % 4096 = 0 (is Aligned = True)
    // 1024 * 4096 is the total amount of bytes that a page table can store/manage.
    // Therefore, to get the directory index we must divide an aligned virtual address to get the directory index.
    // dir_index = virtual_address / (1024 * 4096)

    *dir_index = ((uint32_t) virtual_addr / (PAGING_TOTAL_ENTRIES_PER_TABLE * PAGING_PAGE_SIZE));
    *table_index = ((uint32_t) virtual_addr % (PAGING_TOTAL_ENTRIES_PER_TABLE * PAGING_PAGE_SIZE) / PAGING_PAGE_SIZE);

    return res;
}

int paging_set(uint32_t *dir, void *v_addr, uint32_t ptr)
{
    if(!paging_is_aligned(v_addr))
    {
        return -EINVARG;
    }

    uint32_t dir_index = 0;
    uint32_t table_index = 0;
    int res = paging_get_indexes(v_addr, &dir_index, &table_index);
    if(res<0)
    {
        return res;
    }

    uint32_t directory_entry = dir[dir_index];
    uint32_t *table = (uint32_t *)(directory_entry & 0xFFFFF000);   // Extract 20 bit 4kb page table aligned address only
                                                                    // not the flags
    table[table_index] = ptr;
    return res;
}