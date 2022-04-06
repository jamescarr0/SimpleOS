/**
 * @file disk.c
 * @author James Carr
 * @brief ATA Disk Driver using PIO Mode and LBA28 Addressing for access upto 128Gb.
 * @version 0.1
 * @date 31/03/2022.
 *
 * Uses PIO Mode and LBA28 addressing.  A simple and easy implementation but uses a tremendous amount of CPU resources.
 * Every byte transferred between disk and CPU is sent through the CPU IO Port Bus consuming CPU resources.
 */

#include "disk.h"
#include "io.h"
#include "status.h"
#include "kernelconfig.h"
#include "memory.h"

// Currently, OS only working with a single primary hard disk. Implement a disk array or something in the future?
Disk disk;

static int disk_poll_ready() {

    // Check the BSY Flag in the status register
    // Bit 7 (BSY) - Indicates the drive is preparing to send/receive data (wait for it to clear).
    // In case of 'hang' (it never clears), do a software reset. << Not currently implemented.
    uint8_t bsy = insb(ATA_STATUS);

    while (!(bsy & ATA_STATUS_BSY_FLAG)) {
        bsy = insb(ATA_STATUS);
    }
    return 0;
}


/**
 * Reads 16-bit values one at a time from the ATA controller into memory.
 * @param lba Starting Logical Block address
 * @param total Total amount of sectors to read
 * @param buf The buffer to store the bytes.
 * @return 0 on success, Negative value on error/failure
 *
 * Read from ATA controller copying data into memory.
 * Transfer 256 16-bit values, (uint16_t) at a time, into your buffer from I/O port 0x1F0.
 * Then loop back to waiting for the next IRQ (or poll again -- see next note) for each successive sector.
 */
static int disk_read_sector(const int lba, const int total, const void *const buf) {
    outb(ATA_DRIVE, LBA_MASTER_ADDRESSING(lba));
    outb(ATA_SECTOR_COUNT, total);
    outb(ATA_LBA_LOW, LBA_BITS_LOW(lba));
    outb(ATA_LBA_MID, LBA_BITS_MID(lba));
    outb(ATA_LBA_HIGH, LBA_BITS_HIGH(lba));
    outb(ATA_CMD, LBA_PIO_READ_SECTORS); // 400ns Delay after command. Check BSY

    uint16_t *p = (uint16_t *) buf;

    for (int i = 0; i < total; ++i) {

        if (disk_poll_ready())  // Check bsy flag.
        {
            return -EIO;
        }

        for (int j = 0; j < 256; ++j) {
            *p++ = insw(ATA_PRIMARY_BUS);
        }
    }
    return 0;
}

// Search and initialise disks.
// Currently, only working with a single primary drive.
// Abstraction in place to improve in the future.
void disks_init() {
    memset(&disk, 0, sizeof(disk));
    disk.type = HDD_TYPE_REAL_PRIMARY;
    disk.sector_size = HDD_SECTOR_SIZE;
}

// Return the disk at the corresponding index, currently does nothing really but is written with a view to expanding
// the code to work with multiple disks in the future.
Disk *disk_get(unsigned int disk_index) {
    if (disk_index != 0) {
        return 0;
    }

    return &disk;
}

// Exposed interface for reading blocks from a disk.
int disk_read_block(const Disk *const hdd, unsigned int lba, unsigned int total, void *buf) {
    if (hdd != &disk) {
        return -EIO;
    }

    return disk_read_sector(lba, total, buf);
}