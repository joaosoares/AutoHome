/* Name: main.c
 * Author: Joao Soares, Paulo Carvalho
 * Copyright: Someday...
 * License: None
 */

/* Firmware for a SPI capable LED-Test module. Modules use the AHComm-V1 protocol*/

 #include <avr/io.h>
 #include "AHComm.h"
 #include "LEDTestModuleV1.h"

int main(void)
{
    /* Initialize the module and internal variables */
    /* Setup pin directions and interrupts */
    thismodule.setup();
    /* Setup SPI communication */
	ahcomm.setup();

    for(;;){
        /* Are there serial packets in buffer? */
        if (ahcomm.packetAvailable())
        {
        	/* Create array with size of packet to be read */
        	uint8_t packet[ahcomm.packetSize()];
        	/* Read the body of the packet into packet array */
        	ahcomm.readPacket(packet, ahcomm.packetSize());

        	/* Update system status with information from packet */
        	thismodule.actOn(packet);

        	/* If requested, return a status query */
        	if (thismodule.statusRequested())
        	{
        		/* Create array to store body of status packet */
        		uint8_t array[thismodule.sizeOfPacket()];
        		/* Saves into array the module's current status */
        		thismodule.getStatus(array);
        		/* Packages and sends body through SPI */
        		ahcomm.transmit(array);
        	}
        }
    }
    return 0;   /* never reached */
}

/* Interrupt routine for receiving SPI data */
ISR (SPI_STC_vect)
{
	ahcomm.receive(SPDR);
}
