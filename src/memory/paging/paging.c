//
// Created by James Carr on 24/03/2022.
//

#include "paging.h"
#include "kheap.h"

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
