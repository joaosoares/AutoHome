// Joao Soares Jun 28 2013

#include <WebServer.h>
#include <Ethernet.h>
#include <EthernetBonjour.h>
#include <SPI.h>
#include <Wire.h>

// mac address
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xED};

// set static IP to use if DHCP fails to assign
IPAddress ip(192,168,1,78);

// define prefix value for web server
#define PREFIX ""
WebServer webserver(PREFIX, 80);

// COMMANDS

/* Commands are functions that get called by the webserver framework.
 * They can read any posted data from client, and they output to the
 * server to send data back to the web browser. */
void helloCmd(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
  // this line sends the standard OK headers back to browser
  server.httpSuccess("html");
  
  // HEAD Request
  if (type == WebServer::HEAD)
  {
    return;
  }
  P(helloMsg) = "<html><body><form action=\"\" method=\"POST\"><input type=\"text\" name='amount'/><input type='submit' value='Submit'/></form></body></html>";
  // GET Request
  if (type == WebServer::GET)
  {
    
    server.printP(helloMsg);
  }
  if (type == WebServer::POST)
  {
    char name[16], value[16];
    server.readPOSTparam(name, 16, value, 16);
    if (strcmp(name, "amount         "))
    {
      int val = atoi(value);
      server.printP(helloMsg);
      Serial.println(F("Starting I2C request"));
      Wire.beginTransmission(2);
      char string[7] = "LED   ";
      for (int i = 0; i < 3; i++)
      {
        if (value[i] == '\0')
          break;
        string[i+3] = value[i];
      }
      Wire.write(string);
      Wire.endTransmission();
    }
  }
}


void setup()
{
  Serial.begin(9600);
  // Initialize the Ethernet adapter
  Ethernet.begin(mac);
  delay(1000);
  // Serial.println("Connecting...");
  // print Ip address
  Serial.print(F("IP Address: "));
  for (byte j = 0; j < 4; j++) {
    Serial.print(Ethernet.localIP()[j], DEC);
    Serial.print(F("."));
  }
  Serial.println();
  
  // setup our default command that will be run when the user accesses
  // the root page on the server
  webserver.setDefaultCommand(&helloCmd);
  
  // run the same command if you try to load /index.html
  webserver.addCommand("index.html", &helloCmd);
  
  // start the webserver
  webserver.begin();
  
  // start i2c communication
  Wire.begin();
  // Serial.println("STARTING I2C");
}

void loop()
{
  char buff[64];
  int len = 64;
  
  // Wire.requestFrom(2,6);
  
  // while(Wire.available())
  // {
  //   char c = Wire.read();
  //   Serial.print(c);
  // }
  // Serial.println();
  
  // process incoming connections one at a time forever
  webserver.processConnection(buff, &len);
  
  delay(500);
}