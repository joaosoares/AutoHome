/**
 * AUTOHOME LED TEST MODULE VERSION 1.00 
 * Turn an ATMEGA microcontroller into an LED controller
 *
 * July 2013
 */

#include "module.h"

 /* Declare Variables */
 /**
  * Global status variable bits:
  *  Bit 0: 
  */
 uint8_t status = 0x00;
 /* Start LED brightness at 0 */
 led1_brightness = 0;

/**
 * Setups the module including: Direction of pins,
 * PWM and timer setup.
 */
uint8_t modSetup(void)
{
	// ADD CODE HERE!!!!
}

 /* Parses the body of the packet and evaluates commands */
 uint8_t modActOn(uint8_t body[])
 {
 	/* Loop through all bytes of body */
 	for (int i = 0; i < sizeof(body); i++)
 	{
 		/* Act on individual commands within body */
 		switch(body[i])
 		{
 			/* Set LED to Full ON */
 			case(LED1_ON_CMD):
 				brightness = BRIGHTNESS_MAX;
 				break;
 			/* Set LED to OFF */
 			case(LED1_OFF_CMD):
 				brightness = 0;
 				break;
 			/* Update status flag to signal status query */
 			case(STATUS_REQ_CMD):
 				status |= (1<<STATUS_REQ_FLAG);
 				break;
 			/* CONTINUE LIST OF POSSIBLE COMMANDS */
 		}
 	}

 	/* For future compatibility */
 	return 0;
 }

 /**
  * Returns value corresponding to if status request flag has been triggered
  * Clears the flag after reading.
  */
  uint8_t modStatusRequested()
  {
  	/* Check status bit corresponding to a status request */
  	/* Mask out other bits */
  	if (status & (1<<STATUS_REQ_FLAG))
  	{
  		/* Clear the flag and return 1 */
  		status &= ~(1<<STATUS_REQ_FLAG);
  		return 1;
  	}

  	/* If Status request was not received return 0 */
  	return 0;
  }
 
 /**
  * Updates an array from pointer with the body of a complete
  * status update packet.
  */
 uint8_t modGetStatus(uint8_t body[])
 {
 	/* Byte 1: Global Status Register */
 	body[0] = status;

 	/* Byte 2: Brightness Variable */
 	body[1] = brightness;

 	/* Return 1 to mark sucess */
 	return 1;
 }

 /**
  * Updates the PWM Timer with the new value for brightness
  * and return the previous value of brightness in the timer
  */
 uint8_t modSetBrightness(uint8_t value)
 {
 	// CREATE FUNCTION IN FUTURE
 	return brightness;
 }
 
