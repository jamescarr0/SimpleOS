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
static unsigned int get_byte_total(const unsigned int total)
{
    if(total > HDD_SECTOR_SIZE)
    {
        return HDD_SECTOR_SIZE;
    }

    return total;
}

DiskStream *disk_stream_new(const unsigned int disk_num)
{
    Disk *disk = disk_get(disk_num);
    if(!disk)
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

int disk_stream_read(DiskStream *stream, void *buf, unsigned int total)
{
    int sector = stream->byte_position / HDD_SECTOR_SIZE;
    int offset = stream->byte_position % HDD_SECTOR_SIZE;
    char disk_output[HDD_SECTOR_SIZE];

    int res = disk_read_block(stream->disk, sector, 1, disk_output);
    if(res < 0)
    {
        return res;
    }

    unsigned int read_total = get_byte_total(total);
    for (size_t i = 0; i < read_total; i++)
    {
        *(char*)buf++ = disk_output[offset + i];
    }
    
    stream->byte_position += read_total;
    if(total > HDD_SECTOR_SIZE)
    {
        res = disk_stream_read(stream, disk_output, total-HDD_SECTOR_SIZE);
    }

    return res;
}