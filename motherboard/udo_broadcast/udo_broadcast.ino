#include <Ethernet.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <SPI.h>

byte mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0xFF, 0x45};
IPAddress ip(192,168,2,10);

// local port to listen on
unsigned int localPort = 8888;

// EthernetUDP instance
EthernetUDP Udp;

IPAddress broadcast(255,255,255,255);

  int bytes_written;

void setup() {
  // start Ethernet and UDP
  Ethernet.begin(mac, ip);
  Udp.begin(localPort);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly: 
  Udp.beginPacket(broadcast, 8888);
  bytes_written = Udp.write("Hello, World!");
  Udp.endPacket();  
  Serial.print("Packet sent, with size of: ");
  Serial.println(bytes_written);
  delay(1000);
}
