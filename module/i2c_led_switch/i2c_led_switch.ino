#include <Wire.h>
#include <Module.h>

#define LED 9

Module thisboard("LED", 0);

void setup()
{
  // Serial for debugging
  Serial.begin(9600);
  
  delay(1000);
  
  // Setup LED that will be switched on or off
  pinMode(LED, OUTPUT);
  setBrightness(20);
  
  // I2C
  // join i2c bus with address 2
  Wire.begin(2);
  // Sends current board information to master
  Wire.onRequest(requestEvent);
  // Receives actions from master
  Wire.onReceive(receiveEvent);
 

}

void loop()
{
//  setBrightness(10);
//  delay(1000);
//  char buffer[7];
//  char *data = thisboard.getData(buffer);
//  for (int j = 0; j < 3; j++)
//  { 
//
//    Serial.print(data[j]);
//  }
//  Serial.println(data[4]);
//  
//  setBrightness(98);
//  delay(1000);
//  char new_buffer[7];
//  char *new_data = thisboard.getData(new_buffer);
//  for (int j = 0; j < 3; j++)
//  { 
//
//    Serial.print(new_data[j]);
//  }
//  Serial.println(new_data[4]);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  Serial.println("Sending data via Wire");

  char data[7];
  thisboard.getData(data);
  for (int j = 0; j < 6; j++)
  { 
    Serial.print(data[j]);
  }
  Serial.println();
  
  thisboard.slaveSendData();
  
}

// function that executes when data is received
void receiveEvent(int howMany)
{
  char string[howMany];
  int cur_string_index = 0;
  while(Wire.available()) // loop through all
  {
    if (cur_string_index < howMany) // that is, the cur index is no more than the max # of bytes
    {
      string[cur_string_index] = Wire.read(); // receive byte as a character
      Serial.print(string[cur_string_index]);
      cur_string_index++;
    }
    else
    {
      Wire.read(); // ignore the byte
    }
  }
  Serial.println(string); // print the integer
  setBrightness(thisboard.parseValue(string));
}
  
void setAction(char name[], int value)
{
  if (name == "LED")
  {
    setBrightness(value);
  }
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

