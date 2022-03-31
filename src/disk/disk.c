//
// Created by James Carr on 31/03/2022.
//

#include "disk.h"
#include "io.h"
#include "status.h"
#include "kernelconfig.h"
#include "memory.h"

// Currently, OS only working with a single primary hard disk. Implement a disk array or something in the future?
Disk disk;

static void disk_poll_ready() {
    // Check the BSY Flag in the status register
    // Bit 7 (BSY) - Indicates the drive is preparing to send/receive data (wait for it to clear).
    // In case of 'hang' (it never clears), do a software reset.
    char bsy = insb(ATA_STATUS);
    while (!(bsy & ATA_STATUS_BSY_FLAG)) {
        bsy = insb(ATA_STATUS);
    }
}

static int disk_read_sector(const int lba, const int total, const void *const buf)
{
    outb(ATA_DRIVE, MASTER_LBA_ADDRESSING(lba));
    outb(ATA_SECTOR_COUNT, total);
    outb(ATA_LBA_LOW, LBA_BITS_LOW(lba));
    outb(ATA_LBA_MID, LBA_BITS_MID(lba));
    outb(ATA_LBA_HIGH, LBA_BITS_HIGH(lba));
    outb(ATA_CMD, LBA_PIO_READ_SECTORS); // 400ns Delay after command. Check BSY

    unsigned short *p = (unsigned short*) buf;
    for (int i = 0; i < total; ++i) {
        disk_poll_ready();  // Check bsy flag.

        // Read from ATA controller copying data into memory.
        for (int j = 0; j < 256; ++j) {
            *p++ = insw(ATA_PRIMARY_BUS);
        }
    }
    return 0;
}

// Search and initialise disks.
// Currently, only working with a single primary drive.
// Abstraction in place to improve in the future.
void disks_init()
{
    memset(&disk, 0, sizeof(disk));
    disk.type = HDD_TYPE_REAL_PRIMARY;
    disk.sector_size = HDD_SECTOR_SIZE;
}

Disk *disk_get(unsigned int disk_index)
{
    if (disk_index != 0)
    {
        return 0;
    }

    return &disk;
}

int disk_read_block(Disk *hdd, unsigned int lba, unsigned int total, void *buf)
{
    if(hdd != &disk)
    {
        return -EIO;
    }

    return disk_read_sector(lba, total, buf);
}