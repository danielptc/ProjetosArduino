String leituraSerial;
#include <IRremote.h>
IRsend irsend;

//Padrao sinal RAW Ligar Ar Condicionado SAMSUNG
unsigned int S_pwr[349]={616, 17840, 3032, 8928, 528, 468, 528, 1464, 528, 464, 528, 468, 528, 468, 528, 468, 528, 468, 524, 472, 524, 472, 524, 1488, 508, 488, 452, 540, 452, 1540, 524, 472, 524, 468, 528, 1464, 528, 1460, 528, 1460, 532, 1460, 528, 1464, 528, 468, 528, 468, 524, 472, 524, 492, 508, 488, 452, 544, 496, 496, 524, 472, 524, 472, 528, 468, 528, 464, 532, 464, 532, 464, 528, 464, 532, 464, 532, 464, 532, 464, 528, 468, 528, 468, 528, 468, 528, 468, 524, 492, 512, 484, 452, 544, 496, 496, 524, 472, 524, 472, 528, 464, 532, 464, 532, 464, 532, 464, 532, 460, 532, 1460, 532, 1456, 532, 1460, 532, 1460, 560, 2932, 3032, 8932, 512, 1480, 520, 476, 524, 468, 528, 468, 532, 464, 532, 460, 536, 460, 532, 464, 532, 464, 532, 1456, 532, 464, 532, 464, 532, 1460, 528, 468, 528, 1484, 508, 1480, 500, 1492, 524, 1464, 532, 1456, 536, 1456, 532, 464, 532, 464, 532, 460, 532, 464, 532, 464, 532, 464, 532, 464, 528, 468, 528, 468, 528, 488, 512, 484, 496, 500, 520, 472, 528, 468, 528, 468, 532, 460, 536, 460, 532, 464, 532, 464, 532, 460, 532, 464, 532, 464, 532, 464, 532, 464, 528, 468, 528, 468, 528, 488, 512, 484, 512, 484, 496, 496, 528, 468, 524, 472, 528, 468, 528, 464, 532, 464, 532, 464, 532, 2964, 3004, 8932, 532, 1460, 532, 464, 528, 468, 528, 468, 528, 464, 528, 468, 528, 492, 512, 484, 496, 496, 500, 1488, 528, 468, 528, 468, 532, 464, 532, 464, 528, 1460, 532, 1456, 532, 464, 532, 1460, 528, 1464, 528, 1460, 528, 1484, 456, 1536, 500, 1488, 528, 1464, 528, 1460, 532, 464, 532, 464, 532, 464, 528, 1460, 532, 1460, 528, 1460, 528, 472, 524, 468, 528, 492, 512, 484, 452, 540, 500, 1488, 528, 472, 524, 468, 528, 468, 528, 1460, 532, 1460, 528, 468, 528, 1460, 528, 1464, 528, 468, 524, 472, 524, 492, 512, 484, 452, 544, 452, 544, 496, 496, 524, 1464, 532, 1460, 528, 1460, 532, 1460, 528};


void setup() {
  Serial.begin(9600);
    pinMode(13, OUTPUT);

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


void loop() {



  if (Serial.available() > 0) {


    if (leituraSerial == "ligar") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA
      void ligarAr();
      Serial.println( "ligado");
      
    }
    else if (leituraSerial == "menos") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA

      Serial.println("menos");
    }


    else if (leituraSerial == "mais") { //VERIFICA SE O QUE FOI RECEBIDO VIA SERIAL É IGUAL A STRING ESCRITA
      //digitalWrite(led01, HIGH);
      Serial.println("Mais");
    }

 

    else {
      Serial.println("Não Encontrado!!!");
    }
  }
}


void ligarAr(){
    Serial.println("Ligando...");
    irsend.sendRaw(S_pwr, 349, 38);
    Serial.println("Executando a 38 Hz");
}
