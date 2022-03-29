//
// Created by James Carr on 24/03/2022.
//

#ifndef SIMPLEOS_PAGING_H
#define SIMPLEOS_PAGING_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/*
 * PAGING_CACHE_DISABLED : Bit 4
 * PCD, is the 'Cache Disable' bit. If the bit is set, the page will not be cached. Otherwise, it will be.
 */

#define PAGING_CACHE_DISABLED   0b00010000


/*
 * PAGING_WRITE_THROUGH : Bit 3
 * PWT, controls Write-Through' abilities of the page. If the bit is set, write-through caching is enabled. If not,
 * then write-back is enabled instead.
 */

#define PAGING_WRITE_THROUGH    0b00001000


/*
 * PAGING_ACCESS_FROM_ALL : Bit 2
 * U/S, the 'User/Supervisor' bit, controls access to the page based on privilege level. If the bit is set, then the
 * page may be accessed by all; if the bit is not set, however, only the supervisor can access it. For a page directory
 * directory, the user bit controls access to all the pages referenced by the page directory directory. Therefore, if you wish
 * to make a page a user page, you must set the user bit in the relevant page directory directory as well as the page table
 * directory.
 */

#define PAGING_ACCESS_FROM_ALL  0b00000100


/*
 * PAGING_IS_WRITEABLE : Bit 1
 * R/W, the 'Read/Write' permissions flag. If the bit is set, the page is read/write. Otherwise, when it is not set,
 * the page is read-only. The WP bit in CR0 determines if this is only applied to userland, always giving the kernel
 * write access (the default) or both userland and the kernel (see Intel Manuals 3A 2-20).
 */

#define PAGING_IS_WRITEABLE     0b00000010


/*
 * PAGING_IS_PRESENT : Bit 0
 * P, or 'Present'. If the bit is set, the page is actually in physical memory at the moment. For example, when a page
 * is swapped out, it is not in physical memory and therefore not 'Present'. If a page is called, but not present, a
 * page fault will occur, and the OS should handle it.
 */

#define PAGING_IS_PRESENT       0b00000001


#define PAGING_TOTAL_ENTRIES_PER_TABLE 1024
#define PAGING_PAGE_SIZE 4096


typedef struct {
    uint32_t *directory;
} PagingDir_4gb;

extern void paging_load_dir(uint32_t *);   // asm function

extern void enable_paging(); // asm function.

PagingDir_4gb *init_4gb_page_dir(uint8_t);

uint32_t *paging_get_dir(PagingDir_4gb *);

void paging_switch(uint32_t *directory);

int paging_set(uint32_t *dir, void *v_addr, uint32_t ptr);

#endif //SIMPLEOS_PAGING_H
