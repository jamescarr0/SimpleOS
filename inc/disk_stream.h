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

/**
 * @brief Initialise a new disk stream.
 * 
 * @param disk_num The drive number to stream the data.
 * @return DiskStream* A pointer to the new DiskStream.
 * 
 * A disk stream allows n bytes to be transffered from the disk.
 */
DiskStream *disk_stream_new(const unsigned int disk_num);

/**
 * @brief Set the starting byte address,
 * 
 * @param stream a DiskStream
 * @param pos The byte position to start the read from.
 */
void disk_stream_seek(DiskStream *stream, const unsigned int pos);

/**
 * @brief Read data from a set starting position
 * 
 * @param stream A DiskSteam
 * @param buf The buffer to read data into.
 * @param total Total amount of bytes to read.
 * @return int : 0 on success, negative value on error.
 */
int disk_stream_read(DiskStream *stream, void *buf, unsigned int total);

#endif