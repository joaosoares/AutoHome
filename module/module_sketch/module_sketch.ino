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

// INITIALIZE MODULES AND VARIABLES

AHComm ahcomm();
LEDModule thismodule();

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
  	byte packet[ahcomm.getPacketSize()];
  	ahcomm.readPacket(packet);

  	// Parse value
  	thismodule.actOn(packet);

  	// Send back updated value
  	if (thismodule.statusRequested())
  	{
  		ahcomm.transmit(thismodule.getStatus())
  	}
  }
}

// SPI INTERRUPT
ISR (SPI_STC_vect)
{	
	ahcomm.receive(SPDR);
}