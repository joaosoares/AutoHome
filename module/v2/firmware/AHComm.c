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

 /* State Module ID */
 extern const uint8_t IDENTIFIER[] = {0x00, 0x00, 0x00, 0x01};

 /* Make initial variable definitions */
 /* Hold location of next write in buffer */
 uint16_t buffer_write_index = 0;
 /* Holds location of next read in buffer */
 uint16_t buffer_read_index = 0;
 /**
  * Keeps the length of the next packet to be read. Should be set
  * back to zero after reading the respective packet.
  */
 uint16_t packet_length = 0;
 /* Keeps length of packet in transmit buffer */
 uint16_t transmit_packet_length = 0;

 /**
  * Function initializes the SPI hardware to settings defined in AHCOmm 
  */
 void commSetup()
 {
 	/* Set data direction for SPI pins */
 	DDR_SPI = (1<<DD_MOSI) | (1<<DD_SCK);
 	/* Enable SPI, Set as Slave, Set Clock rate to fck/16 */
 	SPCR = (1<<SPE) | (0<<MSTR) | (1<<SPR0);
 }

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
 			if (receive_buffer[buffer_read_index + j] == STRBYTES)
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
	packet_length = receive_buffer[buffer_read_index + STRBYTES_SIZE + ID_SIZE] << 8;
	packet_length += receive_buffer[buffer_read_index + STRBYTES_SIZE + ID_SIZE + 1];

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
		packet[i] = receive_buffer[buffer_read_index];
		receive_buffer[buffer_read_index] = 0;
	}

	/* For future compatibility */
	return 1
}

/**
 * Checks if the packet is correctly encapsulated by the defined protocol.
 * Returns a byte whose bits correspond to:
 *  Bit 7 (Highest): Passed Checksum
 *  Bit 6: Correct ID
 *  Bit 5: Correct Start Byte 
 */
uint8_t checkPacket(uint16_t start_of_packet)
{
	/* Tracks the packet integrity */
	uint8_t packet_integrity = 0;
	/* Check for sequence of starting bytes */
	uint8_t correct_bytes_num = 0;
	for (int j = 0; j < STRBYTES_SIZE; i++)
	{
		/* Check if byte being read is a valid start byte */
		if (receive_buffer[buffer_read_index + j] == STRBYTES)
		{
			/* Increment tracking of correct bytes */
			correct_bytes_num++;
		}
	}
	/* Continue with Checks */
	if (correct_bytes_num == STRBYTES_SIZE)
	{
		/* Check for the ID ((TO BE IMPLEMENTED!!!)) */
		if (true)
		{
			/* Check the checksum */
			/* Contains computed checksum */
			uint8_t computed_checksum[CHECKSUM_SIZE];
			/* Compute checksum */
			computeChecksum(start_of_packet, computed_checksum, packet_length);
			/* Compare all bytes of checksum */
			/* Keeps track of number of correct checksum bytes */
			correct_bytes_num = 0;
			for (int i = 0; i<CHECKSUM_SIZE; i++)
			{
				if (computed_checksum[i] == receive_buffer[checksum_index+i])
				{
					correct_bytes_num++;
				}
			}
			/* Determine if checksum was correct */
			if (correct_bytes_num == CHECKSUM_SIZE)
			{
				/* Add most significant bit to packet integrity */
				packet_integrity += 0x80;
			}
		}
	}

	/* Returns the integrity of the packet */
	return packet_integrity;
}

/** 
 * Function generates a checksum and saves to array whose pointer
 * was passed as argument to function.
 */
uint8_t computeChecksum(uint16_t start_of_packet, uint8_t checksum, uint16_t length)
{
	/* To be Created */
	return 0;
}

/**
 * This function takes as input the pointer to an array containing of the 
 * body of a packet to be transmitted. it encapsulates the body and adds
 * to the transmit_buffer. The function returns:
 *  0: Buffer Full
 *  1: Packet added to buffer
 *  2-255: Reserved for future use
 */
uint8_t encapsulatePacket(uint8_t body_of_packet)
{

	/**
	 * Check if a start byte is found in buffer. If true, a packet is in 
	 * buffer which is therefore full. 
	 */
	if (transmit_buffer[0] == STRBYTES)
	{
		/* Indicate buffer is full */
		return 0;
	}

	/* Given buffer is not full, start by adding start bytes to packet */
	for (int i = 0; i < STRBYTES_SIZE; i++)
	{
		transmit_buffer[i] = STRBYTES;
	}

	/* Add ID to buffer */
	for (int i = 0; i < sizeof(IDENTIFIER); i++)
	{
		transmit_buffer[i+STRBYTES_SIZE] = IDENTIFIER[i];
	}

	/* Add length to packet */
	/* Determine length of body */
	uint16_t temp_length = sizeof(bodyofpacket[]);
	/* Add upper and lower byte of length separately */
	transmit_buffer[STRBYTES_SIZE+ID_SIZE] = temp_length >> 8;
	transmit_buffer[STRBYTES_SIZE+ID_SIZE] = temp_length;

	/* Add body to message */
	for (int i = 0; i < sizeof(body_of_packet); i++)
	{
		transmit_buffer[HEADER_SIZE + i] = body_of_packet[i];
	}

	/* Add the checksum between the length and the body in buffer */
	/* Create variable to store checksum */
	uint8_t computed_checksum[CHECKSUM_SIZE];
	/* Compute Checksum */
	computeChecksum(body_of_packet, computed_checksum, sizeof(body_of_packet));
	/* Write checksum to buffer */
	for (int i = 0; i<CHECKSUM_SIZE; i++)
	{
		transmit_buffer[STRBYTES_SIZE+ID_SIZE+LENGTH_SIZE+i] = computed_checksum[i];
	}

	/* Save the length of packet into global variable */
	transmit_packet_length = HEADER_SIZE + sizeof(body_of_packet);

	/* Return success */
	return 1;
}

