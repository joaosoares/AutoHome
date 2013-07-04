// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

typedef struct
{
  int value;
  char id[3];
} Device;

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop()
{
  Serial.println("Hi");

  Serial.print(value);

  delay(500);
  
  // debug functions
  digitalWrite(9, HIGH);
  digitalWrite(13, HIGH);
}

Device getSlaveData(int address) 
{
  Device device;
  Wire.requestFrom(2, 4);    // request 6 bytes from slave device #2
  while(Wire.available())    // read first bytes
  { 
    for (int i = 0; i < 3; i++)
    {
      char c = Wire.read(); // receive a byte as character
      device.id[i] = c;
    }

    // now ignore the rest of the bytes until the last
    while (1 < Wire.available())
    {
      Wire.read();
    }
    
    device.value = Wire.read();
  }
  return device;
}

