//
// Created by James Carr on 24/03/2022.
//

#include "paging.h"
#include "kheap.h"

// Create & initialise paging directory.
Paging_4GB_chunk *new_4gb_chunk(uint8_t flags)
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

    Paging_4GB_chunk *chunk = kzalloc(sizeof (Paging_4GB_chunk));
    chunk->dir_entry = dir;
    return chunk;
}

// TODO: Implement paging functions & test.
