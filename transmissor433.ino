/* MSmaker RF Example
 developed by MSmaker
 date: July 7, 2015
 universomakers@gmail.com
 */
#include <VirtualWire.h> //Inclui a biblioteca VirtualWire.h

char *dado ; //Cria a variável que ira armazenar a informação pré definida enviadas pelos botões 

void setup()
{
  //Configura o Arduino para trabalhar como transmissor
  vw_set_ptt_inverted(true);
  vw_setup(2000);
  vw_set_tx_pin(3);//Configura o pino 3 como tx
  //===================================================
  Serial.begin(9600);
  //Configura o estado das portas digitais
  pinMode(3, OUTPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
}

void loop()
{
  if (digitalRead(4) == 0) // Verifica se D4 está pressionado
  {
    dado = "A"; //Armazena o dado pré determinado
    vw_send((uint8_t *)dado, strlen(dado)); //Envia a variável dado
    vw_wait_tx(); //Aguarda o fim de transmissão
    delay(100); //Aguarda um tempo para a próxima leitura
    Serial.println(dado);//Para garantir que os seus botões estão funcionando, você pode verificar no monitor serial
  }
  if (digitalRead(5) == 0) // se estiver pressionado
  {
    dado = "B"; //Armazena o dado pré determinado
    vw_send((uint8_t *)dado, strlen(dado)); //Envia a variável dado
    vw_wait_tx(); //Aguarda o fim de transmissão
    delay(100); //Aguarda um tempo para a próxima leitura
    Serial.println(dado);
  }
  if (digitalRead(6) == 0) // se estiver pressionado
  {
    dado = "C"; //Armazena o dado pré determinado
    vw_send((uint8_t *)dado, strlen(dado)); //Envia a variável dado
    vw_wait_tx(); //Aguarda o fim de transmissão
    delay(100); //Aguarda um tempo para a próxima leitura
    Serial.println(dado);
  }
  if (digitalRead(7) == 0) // se estiver pressionado
  {
    dado = "D"; //Armazena o dado pré determinado
    vw_send((uint8_t *)dado, strlen(dado)); //Envia a variável dado
    vw_wait_tx(); //Aguarda o fim de transmissão
    delay(100); //Aguarda um tempo para a próxima leitura
    Serial.println(dado);
  }
}
