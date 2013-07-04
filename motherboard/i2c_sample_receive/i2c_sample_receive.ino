#include <Wire.h>

#define LED 13

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
}

void loop()
{
  delay(5000);
  Wire.requestFrom(2, 4);    // request 6 bytes from slave device #2
  Serial.println("Requesting...");

  digitalWrite(LED, !digitalRead(LED));
  while(1 < Wire.available())    // slave may send less than requested
  { 
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
  }

  int c = (byte) Wire.read();
  Serial.print(c);
  Serial.println();

  Wire.beginTransmission(2);
  Wire.write("LED50 ")
  Wire.endTransmission();
}
