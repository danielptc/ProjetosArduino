#include "EmonLib.h" //INCLUSÃO DE BIBLIOTECA
#include <ArduinoJson.h>

String leituraSerial;



#define CURRENT_CAL 10.00 //VALOR DE CALIBRAÇÃO (DEVE SER AJUSTADO EM PARALELO COM UM MULTÍMETRO MEDINDO A CORRENTE DA CARGA)
const int leitorCorrente01 = A2; //PINO ANALÓGICO EM QUE O SENSOR ESTÁ CONECTADO
float ruido = 0.08; //RUÍDO PRODUZIDO NA SAÍDA DO SENSOR (DEVE SER AJUSTADO COM A CARGA DESLIGADA APÓS CARREGAMENTO DO CÓDIGO NO ARDUINO)
float wats = 0.00;
float tensao = 120.00;
EnergyMonitor emon1; //CRIA UMA INSTÂNCIA



void setup() {
  Serial.begin(9600);

  
  emon1.current(leitorCorrente01, CURRENT_CAL); //PASSA PARA A FUNÇÃO OS PARÂMETROS (PINO ANALÓGIO / VALOR DE CALIBRAÇÃO)
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
  
  emon1.calcVI(20,100); //FUNÇÃO DE CÁLCULO (20 SEMICICLOS / TEMPO LIMITE PARA FAZER A MEDIÇÃO)
  double currentDraw = emon1.Irms; //VARIÁVEL RECEBE O VALOR DE CORRENTE RMS OBTIDO
  currentDraw = currentDraw-ruido; //VARIÁVEL RECEBE O VALOR RESULTANTE DA CORRENTE RMS MENOS O RUÍDO  
  if(currentDraw < 0){ //SE O VALOR DA VARIÁVEL FOR MENOR QUE 0, FAZ 
      currentDraw = 0; //VARIÁVEL RECEBE 0
  }

  wats = currentDraw * tensao;  
  StaticJsonDocument<200> doc;  
  doc["e"] = "lp";
  doc["ve"] = "10"; 
  doc["c"] = "c";
   
  //serializeJsonPretty(doc, Serial);
  
  serializeJson(doc, Serial);
}


void loop() {


  if (Serial.available() > 0) {

    leituraSerial = leStringSerial();

    if (leituraSerial == "ldr=") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA
       LeitorCorrente01();
    }

    
    else if (leituraSerial == "teste=") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA

      Serial.println("OK");
    }


    else {
      
      Serial.println("Não Encontrado!!!");
    }
  }
}
