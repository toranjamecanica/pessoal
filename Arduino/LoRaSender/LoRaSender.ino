#include "heltec.h"
#define BAND 915E6
#define BOTAOPRETO 12
#define BOTAOAZUL 13
#define LED 25

byte Master = 0xFF;
byte Node1 = 0xCC;
byte Node2 = 0xBB;
String mensage = "" ;



void setup() {

  Heltec.begin(true,true,true,true,BAND);
  //Serial.begin(9600);

}

void loop() {

  Serial.println(digitalRead(BOTAOAZUL));

  if(digitalRead(BOTAOPRETO) == 1)
  {
    sendPack("On", Master, Node1);
    //Serial.println(digitalRead(BOTAOPRETO));
  }

  if(digitalRead(BOTAOAZUL) == 1)
  {
    sendPack("On", Master, Node2);
    Serial.println(digitalRead(BOTAOAZUL));
  }

}

void sendPack(String mensage, byte master, byte node)
{
  LoRa.beginPacket();
  LoRa.write(node);
  LoRa.write(master);
  LoRa.write(mensage.length());
  LoRa.print(mensage);
  LoRa.endPacket();
}