/**
 * AutoHome - Home Automation Project
 * DEVICE MOTHERBOARD FIRMWARE
 *
 * This program is the underlying firmware for Autohome devices
 * with the functions of:
 *  - Communicating with client applications
 *  - Communicating with other devices
 *  - Controling attached modules
 *
 * Started on Jul 17, 2013
 */

#include <SPI.h>
#include <Ethernet.h>
#include <WebServer.h>
#include "modulecomm.h"
//#include "pb.h"
//#include "pb_encode.h"
//#include "pb_decode.h"

// -- VARIABLES AND INITIAL CONFIG --

// ETHERNET
// Mac address
byte mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0xFF, 0x45};
// Set static IP to use if DHCP fails to assign
IPAddress ip(192,168,1,78);

// WEB SERVER 
// Prefix for API access
#define PREFIX ""
// Create instance of server
WebServer webserver(PREFIX, 80);

// CALLBACK
// Time elapsed variable
int time_elapsed;
// Time between callbacks in ms
#define CALLBACK_DELAY 1000

void mainCmd(WebServer &webserver, WebServer::ConnectionType type, char *, bool)
{
  webserver.httpSuccess("application/json");

  // POST Request
  if (type == WebServer::GET)
  {
    webserver.print("{\"name\":\"AutoHome API system\",")
    webserver.print("\"methods\":["
      webserver.print("{\"scheme\":\"overview\",\"description\":\"Returns a bird's eye overview of the system so that the main structure of the client application can be built.\"}"
      webserver.print("{\"scheme\":\"devices\", \"description\":\"A collection of all devices in a system.\"}"
    webserver.print("]}");
  }
}

void setup() 
{
	// SERIAL
	// Initialize serial connection with baud 9600
	Serial.begin(9600);

	// ETHERNET
	// Initialize the Ethernet adapter
	Ethernet.begin(mac);
	delay(500);
	// Print IP address of the connection
	Serial.println("Connected on IP:");
	for (byte j = 0; j < 4; j++)
	{
		Serial.print(Ethernet.localIP()[j], DEC);
		Serial.print(".");
	}
	Serial.println();
	
	// WEBSERVER
	// URL Handlers
	webserver.setDefaultCommand(&mainCmd);
//	webserver.addCommand("/", &mainCmd);

	// CALLBACK
	// Set to current time
	time_elapsed = millis();

}

void loop() 
{
	/* Process incoming connections */
	char buff[64];
	int len = 64;
	webserver.processConnection(buff, &len);

        if (millis() - time_elapsed > CALLBACK_DELAY)
        {
          SPI.begin(4);
          SPI.send(254);
          SPI.send(254);
          SPI.send(254);
          SPI.send(254);
          SPI.send(254);
          SPI.send(254);
          SPI.send(254);
        }

}


