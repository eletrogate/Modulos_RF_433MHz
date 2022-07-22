/* Programa para recepção de Mensagem
  Blog Eletrogate https://blog.eletrogate.com/guia-basico-dos-modulos-tx-rx-rf-433mhz
  Arduino UNO - IDE 1.8.5 - Modulo RX RF 433 MHz
  Gustavo Murta   6/setembro/2018
  Baseado em https://github.com/adafruit/RadioHead/tree/master/examples/ask
*/

#include <RHReliableDatagram.h>                      // biblioteca Radiohead reliableDatagram
#include <RH_ASK.h>                                  // biblioteca Radiohead ASK
#include <SPI.h>                                     // biblioteca SPI

#define TX_ADDRESS 1                                 // endereço do transmissor
#define RX_ADDRESS 2                                 // endereço do receptor 

uint8_t count = 0;                                   // contador
uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];                 // buffer da mensagem
uint8_t tamanho;                                     // tamanho da mensagem
uint8_t from;                                        // endereço de quem transmite

RH_ASK driver;                                       // instância RH ASK
RHReliableDatagram gerente(driver, RX_ADDRESS);      // configurando o gerenciador

void setup()
{
  Serial.begin(9600);                                // inicializa console serial 9600 bps
  if (!gerente.init())                               // se a inicialização do gerenciador falhar
    Serial.println("Falha na inicializacao");        // print na console serial
}

void loop()
{
  if (gerente.available())                           // se gerenciador estiver ativo
  {
    tamanho = sizeof(buf);                           // determina o tamanho do buffer
    if (gerente.recvfromAck(buf, &tamanho, &from))   // se o gerenciador receber mensagem
    {
      Serial.print("Recebido de: 0x");               // print na console serial
      Serial.print(from, HEX);                       // print do endereço do transmissor em Hexadecimal
      Serial.print(": ");                            // print na console serial
      Serial.println((char*)buf);                    // print da mensagem recebida
    }
  }
}