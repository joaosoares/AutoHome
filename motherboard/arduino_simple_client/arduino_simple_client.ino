#include <Ethernet.h>
#include <SPI.h>


// Enter a MAC address and IP address for your controller below
// The IP address will be dependent on your local network
// gateway and subnet are optional:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "www.google.com";

// set static Ip to use if DHCP fails to assign
IPAddress ip(192,168,0,177);

// initialize ethernet client library
// with the ip address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
  // Open serial communications and waits for port to open:
  Serial.begin(9600);
  while(!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to configure using IP address instead of DHCP
    Ethernet.begin(mac, ip);
  }
  // givethe Ethernet shield a second to initialize
  delay(1000);
  Serial.println("connecting...");
  
  // print my local IP address:
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }
  Serial.println();  
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /search?q=arduino HTTP/1.1");
    client.println("Host: www.google.com");
    client.println("Connection: close");
    client.println();
  }
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop()
{
  // if there are incoming bytes available
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  
  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    
    // do nothing forevermore
    while(true);
  }
}
