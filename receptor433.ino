/* MSmaker RF Example
 developed by MSmaker
 date: July 7, 2015
 universomakers@gmail.com
 */
#include <VirtualWire.h> //Inclui a biblioteca VirtualWire.h
#include <Servo.h>

void setup()
{
  int i;
  //Configura o Arduino para trabalhar como receptor
  vw_set_ptt_inverted(true);
  vw_setup(2000);
  vw_set_rx_pin(3);//Configura o pino 3 como rx
  vw_rx_start();
  //=================================================

  pinMode(3, INPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
}


void loop()
{
  char cod;//Cria uma variavel para armazenar o dado recebido.
  uint8_t buf[VW_MAX_MESSAGE_LEN]; //Recebe os dados e armazena na variável buf
  uint8_t buflen = VW_MAX_MESSAGE_LEN; //Armazena na variável buflen o tamanho do dado recebido

  if (vw_get_message(buf, &buflen)) //Pega a mensagem que foi recebida
  {

    cod = buf[0]; //Converte a variável em Char
    Serial.println(cod); //Para verificar valores recebidos e corrigir possiveis erros
    if (cod == 'A') // Compara a informação recebida
    {
      Serial.println(cod); //Para garantir que está recebendo dados, você pode verificar no monitor serial
      digitalWrite(4, !digitalRead(4)); // Inverte o estado da saída D4
    }
    if (cod == 'B')
    {
      Serial.println(cod);
      digitalWrite(5, !digitalRead(5));
    }
    if (cod == 'C')
    {
    }
    if (cod == 'D')
    {
    } 

    
  }

}
