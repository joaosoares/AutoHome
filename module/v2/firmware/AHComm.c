/**
 * AUTO HOME COMMUNICATIONS LIBRARY ACTUAL CODE
 * This library handles all low level communication between the
 * module and the mother board including: Packet forming; Packet
 * parsing; SPI Communication; Error detection.
 *
 * By Joao Soares, Paulo Carvalho
 * July 2013
 */

 /* Include Header File */
 #include "AHComm.h"

 /* Make initial variable definitions */
 /* Hold location of next write in buffer */
 buffer_write_index = 0;
 /* Holds location of next read in buffer */
 buffer_read_index = 0;

 /** 
  * Adds a byte of data into the circular buffer. Updates the 
  * write index in the buffer and circles if necessary.
  */
 uint8_t commReceive(uint8_t data)
 {
	/* Save data into the buffer while incrementing index */
	buffer[buffer_write_index++] = data;

	/* If the write index has reached buffer-end circle back */
	if (buffer_write_index == BUFFER_SIZE)
	{
		buffer_write_index = 0;
	}

	return 1
 }

 /**
  * Returns a true-value if a complete packet is found in buffer.
  * Updates location of the read cursor to oldest correct packet.
  */
 uint8_t commPacketAvailable(void)
 {
 	/* Used to end while loop once a packet is found */
 	bool packet_found = false;

 	/**
 	 * Iterate through buffer searching for a packet until either
 	 * a packet is found or the maximum number of loops has been 
 	 * reached.
 	 */
 	int loop_max = 0;
 	while ((packet_found == 0) && (loop_max<INCOMINGBUFFER_SIZE))
 	{
 		/* Check for sequence of starting bytes */
 		uint8_t correct_bytes_num = 0;
 		for (int j = 0; j < STRBYTES_SIZE; i++)
 		{
 			/* Check if byte being read is a valid start byte */
 			if (buffer[buffer_read_index + j] == STRBYTES)
 			{
 				/* Increment tracking of correct bytes */
 				correct_bytes_num++;
 			}
 		}

 		/**
 		 * Execute a complete packet check if the corret number
 		 * of start bytes has been found at current index.
 		 */
 		if (correct_bytes_num == STRBYTES_SIZE)
 		{
 			/* Check if packet is correct and update while variable*/
 			packet_found = checkPacket(buffer_read_index);
 		}

 		
 		 /* If the pointer does not refer to a valid packet increment */
 		else 
 		{
 			buffer_read_index++;
 		}
 	}
 }

