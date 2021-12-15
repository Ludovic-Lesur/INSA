/*
 * radioFM.h
 *
 * Author: Ludovic Lesur.
 *
 */

#ifndef RADIOFM_H
#define RADIOFM_H


// FM protocol
#define MAGIC_NUMBER 0xAA
#define MY_ADDRESS 0x1F
#define BROADCAST_ADDRESS 0x3F
#define NUMBER_OF_DATA_BYTES 4
#define SIZE_buffer 250
#define BYTES_PER_FRAME 5 // Number of usefull bytes (without OxFF, checksum and @dest).


#endif
