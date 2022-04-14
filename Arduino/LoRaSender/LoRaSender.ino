#include "heltec.h"
#define BAND 915E6
#define BOTAOPRETO 12
#define BOTAOAZUL 13
#define LED 25

// criando IDs unicas para cada loras
byte Master = 0xFF; 
byte Node1 = 0xCC;
byte Node2 = 0xBB;

String mensage = "" ; // string pra salvar mensagens
String comando; // string para salvar o comando do monitor serial
int Status = 0; // gardar status do comando



void setup() {
  Heltec.begin(true,true,true,true,BAND); // configurando biblioteca healtec
  Serial.println("Sistema dessaramdo digite ARMAR para ativar");
}



void loop() {

  if(Serial.available()){ // retorna a quantidade de bites disponivel na porta serial e ao final da string retorna 0
    
    comando = Serial.readStringUntil('\n'); // salvar a string ate o carecter de final de linha
    
    if(comando.equals("ARMAR")) // compara strings se forem iguais retorna 1 
    {
      Status = 1; // altera o status do comando se armado status = 1
      Serial.println("Sistema Armado caso queira desarmar digite DERSAMAR");
      digitalWrite(25,HIGH); // acende o led do esp quando armado
      
    }
    else if(comando.equals("DESARMAR"))
    {
      Status = 0;  // altera o status do comando se desarmado status = 0
      Serial.println("Sistema dessaramdo digite ARMAR para ativar");
      digitalWrite(25,LOW); // apaga o led do esp quando desarmado
    }
    else{
      Serial.println("Comdando Ivalido"); // caso errar o comando retorna mensagem 
    }
  }

  if(digitalRead(BOTAOPRETO) == 1 && Status == 1)// tanto o botão deve estar precionado quanto o  status deve estar = 1 
  {
    sendPack("On", Master, Node1);// chama a função que envia o pacote sendPack(String mensage, byte master, byte node)
    Serial.println("Preto on"); // pinta o staus do botão no monitor serial 
  }

  if(digitalRead(BOTAOAZUL) == 1 && Status == 1)
  {
    sendPack("On", Master, Node2);
    Serial.println("Azul on");
  }

}

void sendPack(String mensage, byte master, byte node)
{
  LoRa.beginPacket(); //inicia o pacote 
  LoRa.write(node); //envia o id do lora de destino
  LoRa.write(master); //envia o id do lora master
  LoRa.write(mensage.length()); //envia o tamanho da mensagem
  LoRa.print(mensage); // envia a mensagem
  LoRa.endPacket(); //finaliza o pacote
}