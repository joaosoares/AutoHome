#include <Wire.h>
#include <Module.h>

#define LED 9

Module thisboard("LED", 0);

// Declare variables
char buf[250]; // Buffer for incoming SPI
volatile byte pos_buffer = 0; // Keeps track of location in buffer
volatile byte process_it = 0; // Indicates number of full packages in buffer
volatile int pos_packet = 0; // Keeps track of location in packet
volatile int len_packet = 0; // Length of incoming packet
volatile byte pos_first_packet = 0; // Saves location of first packet


void setup()
{
  // Serial for debugging
  Serial.begin(115200); 

  // Set OUTPUT pins 
  pinMode(led, OUTPUT);
  pinMode(MISO, OUTPUT);

  // Set SPI as slave mode
  SPCR |= _BV(SPE);

  // Turn on interrupts
  SPI.attachInterrupt();

}




void setBrightness(byte percent)
{
  Serial.println("Changing brightness...");
  // Set boundaries for reveived data
  if (percent < 0) percent = 0;
  if (percent > 100) percent = 100;
  int current = thisboard.getValue();
  thisboard.setValue(percent);
  
  int cur_analog = current * 255/ 100;
  int req_analog = percent * 255/ 100;
  int dim_sign = 1;
  // if requested led value lower than current, loop will decrease
  if (cur_analog == max(cur_analog, req_analog))
  {
    dim_sign = -1;
  }
  int step_val = dim_sign * 5;
  int increasing = cur_analog;
//  while (dim_sign*increasing < dim_sign*req_analog)
//  {
//    analogWrite(LED, increasing);
//    increasing -= step_val;
//    delay(100);
//  }
  // Find out the direction of the increase

  int req_analog_value = percent * 255 / 100;
  analogWrite(LED, req_analog_value);
}

// Interrupt routine for receiving SPI data and placing in buffer
ISR (SPI_STC_vect)
{
  byte c = SPDR // Grab byte form SPI data register

  // If buffer not in end add byte
  if (pos_buffer < sizeof (buf))
    {
    buf [pos_buffer++] = c; // Increment position in buffer
    pos_packet++; // Increment position in packet

    switch (pos_packet)
    {
      case (1):
        if (process_it == 0) // If this is first packet received
        {
          if (pos_buffer != 0)
          {
            pos_first_packet = pos_buffer - 1; // Save the location of its start byte
          }
          else // If current location is first address of buffer
          {
            pos_first_packet = sizeof (buf) - 1; // Save location of start byte as last in buffer
          }        
        }
    }

    if (pos_packet == 5) // If reading first byte of length 
    {
      len_packet = c << 8; // Save as length
    }
    
    if (pos_packet == 6) // If reading second byte of length
    {
      len_packet += c; // Save as part of length
    }

    if (pos_packet == 6 + len_packet) // If full package has been read
    {
      pos_packet = 0; // Indicate position in packet as beginning
      process_it += 1; // Increment flag of available packets in buffer
    }

    }  // end of room available

  else // If end of buffer reached
  {
    
  }
}

