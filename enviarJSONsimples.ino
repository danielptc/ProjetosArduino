#include <ArduinoJson.h>

String leituraSerial;
int valor = 0;
int LDRValue = 0;
#define LDRpin A0


void setup() {
  Serial.begin(9600);

}


void loop() {


  LDRValue = analogRead(LDRpin);

  if (Serial.available() > 0) {

    leituraSerial = leStringSerial();

    if (leituraSerial == "ldr") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA
     
       LeitorCorrente01();
    }

    else if (leituraSerial == "ldr2") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA
       
       LeitorCorrente02();
    }


    else {

      Serial.println("Não Encontrado!");
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


const size_t capacity = JSON_OBJECT_SIZE(3);
DynamicJsonDocument doc(capacity);

doc["ve"] = 100;

serializeJson(doc, Serial);

  //serializeJson(doc, Serial);
}

void LeitorCorrente02() {


const size_t capacity = JSON_OBJECT_SIZE(10);
DynamicJsonDocument doc(capacity);

doc["ve"] = 200;

serializeJson(doc, Serial);

  //serializeJson(doc, Serial);
}
