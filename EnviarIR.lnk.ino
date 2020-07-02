/*
*	Projeto: Automação de Ar condicionado, utilizando sensor eletrônico de Temperatura LM35 e um Emissor de Infra-Vermelho.
*			 Garante que Ar condicionado retorne ligar após uma queda de força elétrica, através do controle de Temperatura do ambiente.
*
*	Bibliotecas utilizadas: 1)para envio do código RAW: IRemote encontrada no site: https://github.com/shirriff/Arduino-IRremote 
*				2)para leitura do sinal: Fora utilizado o Algoritmo encontrado no site abaixo:
*				http://www.analysir.com/blog/wp-content/uploads/2014/03/Arduino_Record_Long_AirConditioner_Infrared_Signals_10.txt
*
*
*	Autor: Deividson Calixto da Silva email: deividsoncs@gmail.com
*/

#include <IRremote.h>
IRsend irsend;

//Padrao sinal RAW Ligar Ar Condicionado SAMSUNG
unsigned int S_pwr[349]={3348, -1644, 464, -1252, 484, -404, 456, -396, 492, -368, 440, -444, 464, -396, 432, -424, 464, -420, 460, -400, 460, -396, 440, -444, 436, -424, 432, -1256, 440, -444, 436, -424, 432, -424, 468, -416, 440, -420, 460, -400, 436, -444, 436, -424, 468, -392, 464, -420, 440, -416, 460, -400, 492, -392, 488, -368, 436, -424, 456, -428, 460, -372, 468, -1248, 436, -448, 432, -1256, 436, -1256, 492, -1224, 432, -1260, 432, -1256, 440, -1252, 464, -420, 460, -1228, 436, -1280, 520, -1172, 440, -1252, 464, -1252, 432, -1256, 440, -1252, 464, -1252, 432, -1260, 464, -392, 520, -364, 432, -400, 456, -404, 488, -420, 436, -424, 508, -348, 460, -424, 432, -428, 432, -1256, 436, -1280, 436, -424, 456, -400, 436, -1280, 440, -1252, 464, -1200, 492, -1252, 488, -368, 488, -372, 432, -1284, 436, -1228, 488, -396, 492, -392, 468, -388, 488, -1180, 464, -444, 436, -424, 464, -1224, 460, -424, 436, -396, 460, -424, 468, -1248, 436, -400, 456, -1232, 464, -1252, 488, -396, 440, -1224, 456, -1260, 492, -1224, 460, -400, 456, -1260, 456, -400, 524, -336, 456, -400, 492, -368, 488, -396, 464, -420, 512, -320, 464, -392, 488, -1256, 492, -1172, 488, -1200, 516, -1228, 436, -1256, 428, -1236, 512, -1228, 468, -1196, 488, -1204, 460, -1280, 468, -1200, 484, -1232, 496, -1192, 492, -368, 488, -396, 496, -388, 436, -396, 484, -372, 464, -420, 492, -368, 488, -368, 512, -1208, 456, -1256, 440, -1228, 464, -416, 496, -1196, 456, -404, 488, -396, 464, -1252, 460, -372, 488, -396, 484, -372, 464, -1228, 468, -440, 440, -1224, 468, -1224, 460, -424, 468, -1248, 436, -1256, 440, -416, 492, -1224, 440, -1252, 464, -420, 440, -392, 464, -420, 440, -1276, 460, -1204, 460, -1232, 516, -368, 456, -400, 492, -1224, 436, -1256, 484, -1232, 496, -336, 488, -396, 464, -396, 460, -396, 464, -420, 512, -372, 464, -368, 460, -424, 464, -396, 492, -392, 468, -1220, 464, -1228, 488, -1204, 492, -1220, 464, -1228, 488, -1228, 488, -1204, 460, -1256, 468, -364, 464, -420, 512, -344, 460, -400, 492, -1224, 460, -396, 460, -400, 512, -1204, 460, -1232, 464, -1224, 460, -1256, 492, -1200, 460, -396, 464, -1252, 536, -1156, 488, -396, 460};

int pinoSensorTemp = 1;
int valorLido = 0;
unsigned long tempoAnterior = 0;
unsigned long tempoIntervalo = 120000; //Tempo de intervalo para leitura da temperatura, em milisegundos.

int enviou = 0;

//#######################IMPORTANTE#######################
//Porta de envio padrao de sinal: PWM 9(MEGA) e 3(PROMINI)

void setup(){
//  Serial.begin(9600);
    pinMode(13, OUTPUT);
}

void loop() {
	//Serial.println(getTemperatura());
	if ((millis() - tempoAnterior) > tempoIntervalo && enviou == 0){
		if (getTemperatura() > 26){
			Serial.println("Enviando Sinal Ligar...");
			ligarAr();
			enviou = 1;
		}
		tempoAnterior = millis();
	}	
	if ((enviou == 1) && ((millis() - tempoAnterior) > 240000)){ //4min.
		enviou = 0;
		Serial.println("Passaram-se 4 minutos... Retornando ao tempo de intervalo normal!");
	}

}

float getTemperatura(){
	valorLido = analogRead(pinoSensorTemp);
	float temperatura = (valorLido * 0.00488);
	temperatura = temperatura * 100;
	return temperatura;
}

void ligarAr(){
    Serial.println("Ligando...");
    irsend.sendRaw(S_pwr, 349, 38);
    Serial.println("Executando a 38 Hz");
}
