/**
 * AUTOHOME LED-SWITCHING MODULE CODE V2
 * The sketch that runs on the modules microcontrollers for the
 * AutoHome home automation project.
 *
 * This module has the standard protocols for AHCommunication between
 * AutoHome devices, and it electronically controls a led connected
 * to a digital pin.
 *
 * July 2013.
 */

#include <SPI.h>
#include <AHComm.h>
#include <Module.h>

// INITIALIZE MODULES AND VARIABLES

AHComm ahcomm();
Module thismodule();
int led = 5;

// SETUP
void setup()
{
	// SPI Init
}

// MAIN LOOP
void loop()
{
  // Check available packets to parse
  if (ahcomm.packetAvailable())
  {
  	// Create local array with size of packet and populate it with data
  	byte packet[ahcomm.packetSize()];
  	ahcomm.readPacket(packet, ahcomm.packetSize());

  	// Parse value
  	thismodule.actOn(packet);

  	/* Send back updated value
  	if (thismodule.statusRequested())
  	{
  		ahcomm.transmit(thismodule.getStatus())
  	}*/
  }
}

// SPI Interrupt Routine
ISR (SPI_STC_vect)
{	
	ahcomm.receive(SPDR);
}

