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
    modSetup();
    /* Setup SPI communication */
	commSetup();

    for(;;){
        /* Are there serial packets in buffer? */
        if (commPacketAvailable())
        {
        	/* Create array with size of packet to be read */
        	uint8_t packet[commPacketSize()];
        	/* Read the body of the packet into packet array */
        	commReadPacket(packet);

        	/* Update system status with information from packet */
        	modActOn(packet);

        	/* If requested, return a status query */
        	if (modStatusRequested())
        	{
        		/* Create array to store body of status packet */
        		uint8_t array[200];
        		/* Saves into array the module's current status */
        		modGetStatus(array);
        		/* Packages and sends body through SPI */
        		commEncapsulatePacket(array);
        	}
        }
    }
    return 0;   /* never reached */
}

/* Interrupt routine for receiving SPI data */
void ISR (SPI_STC_vect)
{
	commReceive(SPDR);
}
