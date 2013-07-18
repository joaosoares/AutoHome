/**
 * AUTOHOME LED TEST MODULE VERSION 1.00 
 * Turn an ATMEGA microcontroller into an LED controller
 *
 * July 2013
 */

 #ifndef Module_h
 #define Module_h

 /* Make Ncessary inclusions */
 #include "avr/io.h"

 /* Possible Commands Preceding Body of Packet */
 #define LED1_ON_CMD 30
 #define LED1_OFF_CMD 31
 #define STATUS_REQ_CMD 32

 /* Defines for shifting into the status flag */
 #define STATUS_REQ_FLAG 0

 /* Define Pins and Devices */
 #define LED1_PIN 9

 /* Module Specific Definitions */
 #define BRIGHTNESS_MAX 255

 /* Declare public functions */
 uint8_t modActOn(uint8_t []);
 uint8_t modStatusRequested();
 uint8_t modGetStatus(uint8_t []);

 /* Declare Private Functions */
 uint8_t setBrightness(uint8_t);

 /* Declare variables */
 uint8_t brightness;
 uint8_t status;

 #endif