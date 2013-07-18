/**
 * AUTO HOME COMMUNICATIONS LIBRARY
 * This library handles all low level communication between the
 * module and the mother board including: Packet forming; Packet
 * parsing; SPI Communication; Error detection.
 *
 * By Joao Soares, Paulo Carvalho
 * July 2013
 */

 #ifndef AHComm_h
 #define AHComm_h

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
 
 /* Make Necessary Inclusions */
 #include "avr/io.h"

 class AHComm
 {
 	public:
	 	/* Declare Public Functions */
	 	AHComm(uint16_t);
	 	uint8_t packetAvailable();
	 	uint16_t packetSize();
	 	uint8_t receive(uint8_t);
	 	void transmit(uint8_t);
	 	void readPacket(uint8_t);

	 	/* Declare Public Variables */
	 	uint16_t module_type;

	 private:
	 	/* Declare Private Functions */
	 	uint8_t checkPacket(uint16_t);

	 	/* Declare Private Variables */
	 	uint8_t buffer[INCOMINGBUFFER_SIZE];
	 	uint16_t buffer_write_index;
	 	uint16_t buffer_read_index;

 };

 #endif
