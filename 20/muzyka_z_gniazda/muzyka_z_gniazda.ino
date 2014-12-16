
#include <SPI.h>  
#include <Ethernet.h>
#include <EthernetUdp.h>        

byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 2);

unsigned int localPort = 1111;     

char packetBuffer[2]; 

EthernetUDP Udp;

char speakerPin = 9;

void setup() {
  Ethernet.begin(mac,ip);
  Udp.begin(localPort);
  pinMode(speakerPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int packetSize = Udp.parsePacket();
  if(packetSize)
  {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    
    Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
    Serial.println("Contents:");
    Serial.print((unsigned int) packetBuffer[0]);
    Serial.print(" ");
    Serial.println((unsigned int) packetBuffer[1]);
    
    tone(speakerPin, map((unsigned int) packetBuffer[1], 0, 128, 131, 1048));
  }
  
  delay(10);
}
