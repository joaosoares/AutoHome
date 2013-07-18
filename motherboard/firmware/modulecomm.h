/**
 * Autohome - Home Automation Project
 * MOTHERBOARD MODULE COMMUNICATION LIBRARY
 *
 * This library serves to standardize connections between
 * the motherboard and its attached modules. The connection
 * happens via SPI. Incoming packets are saved to a circular
 * buffer and later accessed.
 */

/* Packet element type */
typedef struct {
	uint32_t startBytes;
	uint32_t moduleId;
	uint16_t length;
	uint32_t checksum;
	uint8_t data[50];
} PacketType;

/* Circular buffer object */
typedef struct {
	int size; /* maxium number of elements */
	int start; /* index of oldest element */
	int end; /* index at which to write new element */
	PacketType *packets; /* vector of packets */
} CircularBuffer;

/**
 * Initialization function for circular buffer
 * @param cb   the circular buffer type created previously (but has
 *             not been initialized)
 * @param size the size for the buffer
 */
void cbInit(CircularBuffer *cb, int size) {
	cb->size = size + 1; /* include empty elem */
	cb->start = 0;
	cb->end = 0;
	cb->packets = (PacketType *)calloc(cb->size, sizeof(PacketType));
}

/**
 * Frees all spaces in the buffer
 * @param cb The circular buffer
 */
void cbFree(CircularBuffer *cb) {
	free(cb->packets); /* OK if null */
}

/**
 * Returns true if end and start pointers coincide (considering the always
 * open slot)
 * @param  cb The circular buffer
 * @return    1 if full, 0 if not
 */
int cbIsFull(CircularBuffer *cb) {
	return (cb->end + 1) % cb->size == cb->start;
}

/**
 * Returns true if end and start pointers coincide but no always open slot
 * @param  cb The circular buffer
 * @return    1 if empty, 0 if not
 */
int cbIsEmpty(CircularBuffer *cb) {
	return cb->end == cb->start;
}

/**
 * Write an element, overwriting oldest element if buffer is full.
 * To avoid override, check cbIsFull().
 * @param cb     The circular buffer
 * @param packet The packet that will be written
 */
void cbWrite(CircularBuffer *cb, PacketType *packet) {
	cb->packets[cb->end] = *packet;
	cb->end = (cb->end + 1) % cb->size;
	if (cb->end == cb->start) /* increment start byte if buffer is full */
		cb->start = (cb->start + 1) % cb->size;
}

/**
 * Writes a single byte to the circular buffer
 * @param cb   The circular buffer
 * @param byte The byte to be written
 */
//void cbWriteByte(CircularBuffer *cb, uint8_t *byte) {
//	cb->packets[cb->end] = *byte;
//	cb->end = (cb->end + 1) % cb->size;
//	if (cb->end == cb->start) /* see function above for explanation */
//		cb->start = (cb->start + 1) % cb->size
//}

/**
 * Read oldest element. Must ensure !cbIsEmpty() first.
 * @param cb     [description]
 * @param packet [description]
 */
void cbRead(CircularBuffer *cb, PacketType *packet) {
	*packet = cb->packets[cb->start];
	cb->start = (cb->start + 1) % cb->size;
}
