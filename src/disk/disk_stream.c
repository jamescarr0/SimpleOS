/**
 * @file disk_stream.c
 * @author James Carr
 * @brief Creates a stream to read n bytes into memory.
 * @version 0.1
 * @date 07/04/2022.
 *
 */

#include "disk_stream.h"
#include "status.h"
#include "kernelconfig.h"
#include "kheap.h"
#include <stddef.h>

/**
 * @brief Get the read amount object
 *
 * @param total
 * @return unsigned int
 */
static unsigned int get_byte_total(unsigned int total, const unsigned int offset)
{
    /*
    Check for overflow.  Make sure that the total number of bytes to read
    does not exceed our buffer size.  If it does, adjust the total number of
    bytes to read accordingly.
    */
    if (total + offset >= HDD_SECTOR_SIZE)
    {
        total -= (offset + total) - HDD_SECTOR_SIZE;
    }

    return total;
}

DiskStream *disk_stream_new(const unsigned int disk_num)
{
    Disk *disk = disk_get(disk_num);
    if (!disk)
    {
        return -EINVDSK;
    }

    DiskStream *stream = kzalloc(sizeof(DiskStream));
    stream->byte_position = 0;
    stream->disk = disk;

    return stream;
}

void inline disk_stream_seek(DiskStream *stream, const unsigned int pos)
{
    stream->byte_position = pos;
}

/*
Calculate sector and offset, disk_stream_seek will have set the byte position
to the address it was passed.
For example:
If we wanted to read bytes from offset 0x90 (decimal 144)
144 / 512 = 0.28125, Therefore the sector is 0.
144 % 512 = 144, Therefore, the data we need from the buffer starts at
the offset of 144.
*/
int disk_stream_read(DiskStream *stream, void *buf, unsigned int total)
{
    int res = 0;
    int sector = 0;
    int offset = 0;
    char disk_output[HDD_SECTOR_SIZE] = {0};
    unsigned int read_total = 0;

    while (total != 0)
    {
        sector = stream->byte_position / HDD_SECTOR_SIZE;
        offset = stream->byte_position % HDD_SECTOR_SIZE;

        res = disk_read_block(stream->disk, sector, 1, disk_output);
        if (res < 0)
        {
            return res;
        }

        // Get_byte_total will adjust for any overflow due to offset.
        read_total = get_byte_total(total, offset);

        for (size_t i = 0; i < read_total; i++)
        {
            *(char *)buf++ = disk_output[offset + i];
        }
        stream->byte_position += read_total;
        total -= read_total;
    }
    return res;
}