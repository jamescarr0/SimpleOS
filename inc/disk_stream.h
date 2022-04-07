/**
 * @file disk_stream.h
 * @author James Carr
 * @brief Prototypes for creating a disk stream to read n bytes into memory.
 * @version 0.1
 * @date 07/04/2022.
 *
 * Read blocks of data from the hard drive and track the byte position when reading into the buffer.
 * This ensures we will not overflow the buffer inside the decleartion, and returns n bytes requested.  
 * Abstracts away having to deal with sectors.
 * 
 * For example : 
 * If 100 bytes are requested, then 100 bytes will be returned, rather than an entire sector (512bytes).
 * 
 */

#ifndef SIMPLEOS_DISK_STREAM_H
#define SIMPLEOS_DISK_STREAM_H

#include "disk.h"

/**
 * @brief Track the byte position when reading from a disk stream into buffer.
 * 
 * byte_position : Represents the current byte position in the disk stream.
 * disk : The disk being read from.
 *
 */
typedef struct DiskStream_s {
    int byte_position;
    struct Disk_s *disk;
} DiskStream;

DiskStream *disk_stream_new(const unsigned int disk_num);

void disk_stream_seek(DiskStream *stream, const unsigned int pos);

int disk_stream_read(DiskStream *stream, void *buf, unsigned int total);

#endif