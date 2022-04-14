#include "heltec.h"
#define BAND 915E6
#define BOTAO 12
#define LED 25

// criando IDs unicas para cada loras
byte Master = 0xFF;
byte Node1 = 0xCC;
byte Node2 = 0xBB;
// string pra salvar mensagens
String mensage = "" ;



void setup() {

  Heltec.begin(true,true,true,true,BAND);// configurando biblioteca healtec
  
}

void loop() {


  reciver(LoRa.parsePacket());// chama a funçao que recebe e le pacotes 
 
}


void reciver(int packsize) { 

  if(packsize == 0) return;//se não ha pacotes para receber, retorna


  int remetente = LoRa.read(); // salva o id do remetente
  byte  sender = LoRa.read();  // salva a id do lora destinatario
  
  String incomig = ""; // string para criar mensagem

  while (LoRa.available())
  {
    incomig += (char)LoRa.read(); 
  }

  if(remetente != Node1 && remetente != Master) // o id de rementente e destinatarios não forem iguais retorna 
  {
    Serial.println("Essa mensagem nao é pra mim");
    return;
  }

 //se forem iguais piscar o led do lora 

  digitalWrite(25,HIGH);
  delay(100);
  digitalWrite(25,LOW);

 // infos da mensagem no monitor serial
  Serial.println(incomig);
  Serial.println(sender);
  Serial.println(remetente);

  

}

