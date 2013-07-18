/**
 * AUTO HOME COMMUNICATIONS LIBRARY HEADER FILE
 * This library handles all low level communication between the
 * module and the mother board including: Packet forming; Packet
 * parsing; SPI Communication; Error detection.
 *
 * By Joao Soares, Paulo Carvalho
 * July 2013
 */

 #ifndef AHComm_h
 #define AHComm_h

 /* Make Necessary Inclusions */
 #include "avr/io.h"

 /* Make Definitions Regarding Packet Format and Size */
 #define STRBYTES 254
 #define STRBYTES_SIZE 2
 #define ID_SIZE 4
 #define LENGTH_SIZE 2
 #define CHECKSUM_SIZE 2
 #define HEADER_SIZE STRBYTES_SIZE+ID_SIZE+LENGTH_SIZE+CHECKSUM_SIZE

 /* Make Internal Definitions */
 /* Size of circular buffer for incoming packets */
 #define INCOMINGBUFFER_SIZE 255

/* Declare Function Prototypes */
uint8_t commPacketAvailable(void);
uint16_t commPacketSize(void);
uint8_t commReceive(uint8_t);
void commTransmit(uint8_t);
uint8_t commReadPacket(uint8_t);
static uint8_t checkPacket(uint16_t);
static uint8_t computeChecksum(uint8_t);


/* Declare Private Variables */
uint8_t buffer[INCOMINGBUFFER_SIZE];
uint8_t computed_checksum[CHECKSUM_SIZE];
uint16_t buffer_write_index;
uint16_t buffer_read_index;
uint16_t module_type;

 #endif
