#include "heltec.h"
#define BAND 915E6
#define BOTAO 12
#define LED 25
#define A1 17
#define CHAVE "Armado"
#define CHAVE2 "Desarmar"
int contador = 0;
char caracter;
String chave = "";
String mensage = "";



void setup () {
Heltec.begin(true, true, true, true, BAND);//(Ativar display,Ativar LoRa,Ativar comunicação serial,definir banda


pinMode(A1,INPUT);

//define a palavra de sincronização
LoRa.setSyncWord(0xF3);
Serial.println("LoRa iniciado");
Serial.println("Aguando comando 1");

digitalWrite(A1,LOW);

mensage = "Desermado";
display(mensage,45);

}

void loop () {
//Serial.print("Envio de pacote:");
//Serial.println(contador);
contador ++;

chave = Serial.readString();



if(chave == CHAVE)
{
  Serial.println(chave);
  digitalWrite(A1,HIGH);
  mensage = "Armado";
  display(mensage,45);
}
else if(chave == CHAVE2)
{
  mensage = "Desermado";
  display(mensage,45);
}


LoRa.beginPacket();//crianado pacote
LoRa.print(digitalRead(BOTAO));//armazenado estado do botão
LoRa.endPacket();//finalizando pacote

if(digitalRead(BOTAO) == HIGH)
{
  mensage = "Botão Precionado";
  display(mensage,0);
}
else
{
  mensage = "Lora Sender";
  display(mensage,0);

}

Serial.println(digitalRead(BOTAO));

//Piscando LED
digitalWrite(LED, HIGH);
delay(400);
digitalWrite(LED, LOW);
delay(400);
}

void display (String mensagem , int linha)
{
  
  Heltec.display->setContrast(255);
  Heltec.display->clear();
  Heltec.display->setFont(ArialMT_Plain_16);
  Heltec.display->drawString(0, linha, mensagem);
  Heltec.display->display();
  
}