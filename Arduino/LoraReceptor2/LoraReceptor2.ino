#include "heltec.h"
#define BAND 915E6
#define BOTAO 12
#define LED 25

byte Master = 0xFF;
byte Node1 = 0xCC;
byte Node2 = 0xBB;
String mensage = "" ;



void setup() {

  Heltec.begin(true,true,true,true,BAND);
  
}

void loop() {


  reciver(LoRa.parsePacket());
 
}


void reciver(int packsize) {

  if(packsize == 0) return;

  int remetente = LoRa.read();
  byte  sender = LoRa.read();
  byte  msgId = LoRa.read();

  String incomig = "";

  while (LoRa.available())
  {
    incomig += (char)LoRa.read();
  }

  if(remetente != Node1 && remetente != Master) 
  {
    Serial.println("Essa mensagem nao é pra mim");
    return;
  }

  digitalWrite(25,HIGH);
  delay(100);
  digitalWrite(25,LOW);

  Serial.println(incomig);
  Serial.println(sender);
  Serial.println(remetente);

  

}

