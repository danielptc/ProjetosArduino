#include <IRremote.h>
#include "EmonLib.h" //INCLUSÃO DE BIBLIOTECA LEITOR DE CORRENTE
#include <ArduinoJson.h>
#include <RCSwitch.h>

String leituraSerial;
int valor = 0;
int LDRValue = 0;
#define LDRpin A0

#define Tomada01 3
#define Tomada02 4
#define Tomada03 5
#define Sala 7

#define LedPower 13

byte Status_Sala = 0;
byte Status_Dormitorio01 = 0;
byte Status_Dormitorio02 = 0;
byte Status_Cozinha = 0;

#define CURRENT_CAL 10.00 //VALOR DE CALIBRAÇÃO (DEVE SER AJUSTADO EM PARALELO COM UM MULTÍMETRO MEDINDO A CORRENTE DA CARGA)
const int leitorCorrente01 = A2; //PINO ANALÓGICO EM QUE O SENSOR ESTÁ CONECTADO
float ruido = 0.08; //RUÍDO PRODUZIDO NA SAÍDA DO SENSOR (DEVE SER AJUSTADO COM A CARGA DESLIGADA APÓS CARREGAMENTO DO CÓDIGO NO ARDUINO)
float wats = 0.00;
float tensao = 120.00;
EnergyMonitor emon1; //CRIA UMA INSTÂNCIA

int khz = 38;
IRsend irsend;

RCSwitch mySwitch = RCSwitch();

////////////////////////////////CODIGOS DATASHOW///////////////////////////////////////
unsigned int Ligar_DataShow[135] = {8800, 4350, 650, 1600, 600, 1600, 600, 450, 600, 500, 600, 500, 600, 550, 550, 550, 550, 1650, 550, 1650, 550, 550, 550, 1600, 600, 550, 550, 1600, 600, 500, 600, 1600, 600, 500, 600, 550, 550, 550, 600, 500, 600, 500, 600, 1600, 600, 500, 600, 500, 600, 1600, 600, 1650, 550, 1650, 500, 1650, 550, 1650, 550, 500, 600, 1600, 600, 1650, 550, 500, 650, 40050, 8800, 4350, 650, 1600, 550, 1650, 550, 500, 600, 500, 600, 500, 600, 500, 600, 550, 550, 1600, 600, 1650, 550, 500, 600, 1600, 600, 500, 600, 1600, 600, 500, 600, 1600, 600, 500, 600, 500, 650, 500, 600, 500, 600, 500, 600, 1600, 550, 550, 600, 500, 600, 1600, 600, 1650, 550, 1600, 550, 1650, 550, 1650, 550, 500, 650, 1550, 600, 1600, 600, 500, 600};

unsigned int Congelar[135] = {8800, 4350, 600, 1650, 550, 1600, 600, 500, 650, 450, 650, 450, 650, 500, 600, 500, 600, 1550, 600, 1650, 550, 500, 650, 1550, 600, 500, 600, 1600, 600, 500, 600, 1600, 600, 500, 600, 550, 600, 1550, 600, 500, 600, 550, 600, 1550, 600, 550, 550, 550, 600, 1600, 550, 1650, 550, 550, 600, 1550, 600, 1650, 550, 500, 650, 1550, 600, 1600, 600, 500, 600, 40100, 8800, 4350, 600, 1600, 600, 1600, 600, 500, 600, 500, 600, 500, 650, 450, 650, 450, 650, 1550, 600, 1650, 550, 500, 650, 1550, 600, 500, 600, 1600, 600, 500, 600, 1600, 600, 500, 600, 500, 650, 1550, 600, 500, 600, 500, 650, 1550, 600, 500, 600, 550, 600, 1550, 600, 1650, 550, 500, 650, 1550, 600, 1600, 600, 500, 600, 1600, 600, 1600, 600, 500, 600};

unsigned int Video[135] = {8800, 4350, 600, 1650, 550, 1650, 550, 500, 600, 500, 650, 450, 650, 450, 650, 500, 600, 1550, 650, 1600, 600, 450, 650, 1550, 650, 450, 650, 1550, 600, 500, 650, 1550, 600, 500, 650, 450, 650, 500, 600, 500, 600, 500, 600, 1600, 600, 1600, 550, 1650, 550, 500, 650, 1550, 600, 1650, 550, 1600, 600, 1600, 600, 500, 600, 500, 600, 500, 650, 1550, 600, 40100, 8800, 4350, 600, 1650, 550, 1600, 600, 500, 600, 500, 600, 500, 650, 450, 650, 450, 650, 1550, 650, 1550, 600, 500, 600, 1600, 600, 500, 650, 1550, 600, 500, 600, 1600, 600, 500, 600, 500, 650, 450, 650, 500, 600, 500, 600, 1600, 550, 1650, 550, 1650, 550, 500, 600, 1600, 600, 1600, 600, 1600, 600, 1600, 550, 550, 550, 550, 600, 500, 600, 1600, 600};

unsigned int Automatico[135] = {8800, 4350, 650, 1600, 600, 1550, 600, 500, 550, 550, 600, 500, 600, 500, 600, 500, 600, 1600, 600, 1650, 550, 500, 600, 1600, 600, 500, 600, 1600, 600, 500, 600, 1600, 550, 550, 600, 500, 600, 500, 600, 1600, 600, 500, 600, 1600, 600, 500, 600, 500, 600, 1600, 600, 1650, 550, 1650, 500, 550, 600, 1600, 550, 550, 600, 1600, 600, 1600, 550, 550, 600, 40100, 8800, 4350, 650, 1550, 600, 1600, 600, 450, 600, 550, 550, 550, 600, 500, 600, 500, 600, 1600, 600, 1650, 500, 550, 600, 1600, 550, 550, 600, 1600, 550, 550, 600, 1600, 550, 550, 600, 500, 600, 500, 650, 1550, 600, 500, 600, 1600, 550, 550, 600, 500, 600, 1600, 600, 1650, 550, 1650, 500, 550, 600, 1550, 600, 550, 600, 1550, 600, 1650, 550, 500, 650};



void setup() {
  Serial.begin(9600);
  pinMode(Tomada01, OUTPUT);
  pinMode(Tomada02, OUTPUT);
  pinMode(Tomada03, OUTPUT);
  pinMode(Sala, OUTPUT);

  //pinMode(LedPower, OUTPUT);

  emon1.current(leitorCorrente01, CURRENT_CAL); //PASSA PARA A FUNÇÃO OS PARÂMETROS (PINO ANALÓGIO / VALOR DE CALIBRAÇÃO)

  mySwitch.enableTransmit(10);

  digitalWrite(LedPower, HIGH);

}


void loop() {


  LDRValue = analogRead(LDRpin);

  if (Serial.available() > 0) {

    leituraSerial = leStringSerial();

    if (leituraSerial == "ldr=") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA
      LeitorCorrente01();
    }


    else if (leituraSerial == "valor sensor 01") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA

      Serial.println(valor + 5 * valor);
    }


    else if (leituraSerial == "tomada01_ligada") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA
      digitalWrite(Tomada01, HIGH);
      //Status_Sala = 1;
    }


    else if (leituraSerial == "tomada01_desligada") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA
      digitalWrite(Tomada01, LOW);
      //Status_Sala = 0;
    }

    else if (leituraSerial == "tomada02_ligada") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA
      digitalWrite(Tomada02, HIGH);
      //Status_Cozinha = 2;
    }


    else if (leituraSerial == "tomada02_desligada") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA
      digitalWrite(Tomada02, LOW);
      //Status_Cozinha = 0;
    }

    else if (leituraSerial == "tomada03_ligada") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA
      digitalWrite(Tomada03, HIGH);
      //Status_Cozinha = 2;
    }


    else if (leituraSerial == "tomada03_desligada") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA
      digitalWrite(Tomada03, LOW);
      //Status_Cozinha = 0;
    }

    else if (leituraSerial == "cozinha_ligada") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA
      digitalWrite(Sala, HIGH);
      //Status_Cozinha = 2;
    }


    else if (leituraSerial == "cozinha_desligada") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA
      digitalWrite(Sala, LOW);
      //Status_Cozinha = 0;
    }



    else if (leituraSerial == "sala_quadro_ligado") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA
      mySwitch.send(1, 23);
      //Serial.println("ok");
    }


    else if (leituraSerial == "sala_quadro_desligado") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA
      mySwitch.send(2, 23);
      //Serial.println("ok");
    }


    else if (leituraSerial == "sala_fundo_ligado") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA
      mySwitch.send(3, 23);
      //Serial.println("ok");
    }


    else if (leituraSerial == "sala_fundo_desligado") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA
      mySwitch.send(4, 23);
      //Serial.println("ok");
    }

    else if (leituraSerial == "sala_toda_desligado") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA
      mySwitch.send(5, 23);
      //Serial.println("ok");
    }

    else if (leituraSerial == "sala_toda_ligado") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA
      mySwitch.send(6, 23);
      //Serial.println("ok");
    }



    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////ENVIO DE DADOS DATASHOW//////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    else if (leituraSerial == "datashowLigado") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA
      irsend.sendRaw(Ligar_DataShow, sizeof(Ligar_DataShow) / sizeof(Ligar_DataShow[0]), khz);

    }

    else if (leituraSerial == "datashowCongelar") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA
      irsend.sendRaw(Congelar, sizeof(Congelar) / sizeof(Congelar[0]), khz);

    }


    else if (leituraSerial == "dataShowVideo") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA
      irsend.sendRaw(Video, sizeof(Video) / sizeof(Video[0]), khz);

    }



    else if (leituraSerial == "datashowAutomatico") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA
      irsend.sendRaw(Automatico, sizeof(Automatico) / sizeof(Automatico[0]), khz);

    }


    else if (leituraSerial == "ligarSom") {
      for (int i = 0; i < 3; i++) {
        irsend.sendNEC(0xFFA25D, 32);
        delay(40);
      }
    }

    else if (leituraSerial == "modoOperacao") {
      for (int i = 0; i < 3; i++) {
        irsend.sendNEC(0xFF629D, 32);
        delay(40);
      }
    }

    else if (leituraSerial == "semSom") {
      for (int i = 0; i < 3; i++) {
        irsend.sendNEC(0xFFE21D, 32);
        delay(40);
      }
    }

    else if (leituraSerial == "playPause") {
      for (int i = 0; i < 3; i++) {
        irsend.sendNEC(0xFF22DD, 32);
        delay(40);
      }
    }

    else if (leituraSerial == "anterior") {
      for (int i = 0; i < 3; i++) {
        irsend.sendNEC(0xFF02FD, 32);
        delay(40);
      }
    }

    else if (leituraSerial == "proximo") {
      for (int i = 0; i < 3; i++) {
        irsend.sendNEC(0xFFC23D, 32);
        delay(40);
      }
    }

    else if (leituraSerial == "scan") {
      for (int i = 0; i < 3; i++) {
        irsend.sendNEC(0xFFB04F, 32);
        delay(40);
      }
    }

    else if (leituraSerial == "volumeMenos") {
      for (int i = 0; i < 3; i++) {
        irsend.sendNEC(0xFFA857, 32);
        delay(40);
      }
    }

    else if (leituraSerial == "volumeMais") {
      for (int i = 0; i < 3; i++) {
        irsend.sendNEC(0xFF906F, 32);
        delay(40);
      }
    }


    else if (leituraSerial = "status") {
      Status ();
    }


    else {

      Serial.println("Não Encontrado!!!");
    }
  }
}



String leStringSerial() { //FUNÇÃO QUE FAZ A LEITURA DO SERIAL E RETORNA O VALOR

  String valorSerial = "";
  char leituraSerial;

  // Enquanto receber algo pela serial
  while (Serial.available() > 0) {
    // Lê byte da serial
    leituraSerial = Serial.read();
    // Ignora caractere de quebra de linha
    if (leituraSerial != '\n') {
      // Concatena valores
      valorSerial.concat(leituraSerial);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }

  return valorSerial;
}



void LeitorCorrente01() {

  emon1.calcVI(20, 100); //FUNÇÃO DE CÁLCULO (20 SEMICICLOS / TEMPO LIMITE PARA FAZER A MEDIÇÃO)
  double currentDraw = emon1.Irms; //VARIÁVEL RECEBE O VALOR DE CORRENTE RMS OBTIDO
  currentDraw = currentDraw - ruido; //VARIÁVEL RECEBE O VALOR RESULTANTE DA CORRENTE RMS MENOS O RUÍDO
  if (currentDraw < 0) { //SE O VALOR DA VARIÁVEL FOR MENOR QUE 0, FAZ
    currentDraw = 0; //VARIÁVEL RECEBE 0
  }

  wats = currentDraw * tensao;

  StaticJsonDocument<200> doc;
  doc["ve"] = 100;
  doc["e"] = "LP";
  doc["c"] = "C";
  //serializeJsonPretty(doc, Serial);

  serializeJson(doc, Serial);
}


void Status () {

  StaticJsonDocument<200> doc;
  doc["S"] = Status_Sala;
  doc["D1"] = Status_Dormitorio01;
  doc["D2"] = Status_Dormitorio02;
  doc["C"] = Status_Cozinha;
  //serializeJsonPretty(doc, Serial);

  serializeJson(doc, Serial);


}
