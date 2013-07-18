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
  * Keeps the length of the next packet to be read. Should be set
  * back to zero after reading the respective packet.
  */
 packet_length = 0;

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
 			if (checkPacket(buffer_read_index) == 1)
 			{
 				packet_found = true;
 			}
 			
 		}

 		 /* If the pointer does not refer to a valid packet increment */
 		else 
 		{
 			buffer_read_index++;
 		}
 	}

 	/**
 	 * Return: 
 	 * 	0 if no packet found
 	 * 	1 if packet found
 	 * 	2-255 RESERVED FOR FUTURE USE
 	 */
 	
 	if (packet_found)
 	{
 		return 1;
 	}

 	return 0;
 }

/**
 * Returns the size of the packet at current read index.
 * The function assumes that the read index is updated and an
 * ideal packet is present at the given location. Function 
 * read two bytes and concatenates into a single integer to return.
 */
uint16_t commPacketSize(void)
{
	/* Read the LENGTH at the header defined by the protocol */
	packet_length = buffer[buffer_read_index + STRBYTES_SIZE + ID_SIZE] << 8;
	packet_length += buffer[buffer_read_index + STRBYTES_SIZE + ID_SIZE + 1];

	return packet_length;
}

/**
 * Returns the body of the packet at the current location of the read index.
 * Assumes the packet has been checked and passed. After reading destroys 
 * the packet by writing zeroes to location.
 */
uint8_t commReadPacket(uint8_t array[])
{
	/* Erase header of packet and increment index till body*/
	for (int i = 0; i<HEADER_SIZE; i++)
	{
		array[buffer_read_index++] = 0;
	}
	/* Iterate over the body of packet and save to array */
	for (uint16_t i = 0; i < (packet_length-HEADER_SIZE); i++)
	{
		/* increment the temporary index */
		buffer_read_index++;
		/* Wrap around end of buffer has been reached */
		if (buffer_read_index >= INCOMINGBUFFER_SIZE)
		{
			buffer_read_index -= INCOMINGBUFFER_SIZE;
		}
		/* Read Byte of Body then erase byte from buffer*/
		packet[i] = buffer[buffer_read_index];
		buffer[buffer_read_index] = 0;
	}

	/* For future compatibility */
	return 1
}

/**
 * Checks if the packet is correctly encapsulated by the defined protocol.
 * Returns:
 *  0 if general error is found
 *  1 if packet is correct
 *  2-255 RESERVED FOR FUTURE
 */
uint8_t checkPacket(uint16_t start_of_packet)
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

	/* Continue with Checks */
	if (correct_bytes_num == STRBYTES_SIZE)
	{
		/* Check for the ID TO BE IMPLEMENTED!!! */
		if (true)
		{
			/* Check the checksum */
			if 
		}
	}
}

