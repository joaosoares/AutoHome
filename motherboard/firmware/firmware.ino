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
 * Started by João Soares on Jul 17, 2013
 */
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <WebServer.h>

// -- VARIABLES AND INITIAL CONFIG --

// ETHERNET
// Mac address
byte mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0xFF, 0x45};
// Set static IP to use if DHCP fails to assign
IPAddress ip(192,168,1,78);

// WEB SERVER 
// Prefix for API access
#define PREFIX "api"
// Create instance of server
WebServer webserver(PREFIX, 80);

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
	webserver.setDefaultCommand(&main);
	webserver.addCommand("")
}