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
unsigned int S_pwr[349]={616, 17840, 3032, 8928, 528, 468, 528, 1464, 528, 464, 528, 468, 528, 468, 528, 468, 528, 468, 524, 472, 524, 472, 524, 1488, 508, 488, 452, 540, 452, 1540, 524, 472, 524, 468, 528, 1464, 528, 1460, 528, 1460, 532, 1460, 528, 1464, 528, 468, 528, 468, 524, 472, 524, 492, 508, 488, 452, 544, 496, 496, 524, 472, 524, 472, 528, 468, 528, 464, 532, 464, 532, 464, 528, 464, 532, 464, 532, 464, 532, 464, 528, 468, 528, 468, 528, 468, 528, 468, 524, 492, 512, 484, 452, 544, 496, 496, 524, 472, 524, 472, 528, 464, 532, 464, 532, 464, 532, 464, 532, 460, 532, 1460, 532, 1456, 532, 1460, 532, 1460, 560, 2932, 3032, 8932, 512, 1480, 520, 476, 524, 468, 528, 468, 532, 464, 532, 460, 536, 460, 532, 464, 532, 464, 532, 1456, 532, 464, 532, 464, 532, 1460, 528, 468, 528, 1484, 508, 1480, 500, 1492, 524, 1464, 532, 1456, 536, 1456, 532, 464, 532, 464, 532, 460, 532, 464, 532, 464, 532, 464, 532, 464, 528, 468, 528, 468, 528, 488, 512, 484, 496, 500, 520, 472, 528, 468, 528, 468, 532, 460, 536, 460, 532, 464, 532, 464, 532, 460, 532, 464, 532, 464, 532, 464, 532, 464, 528, 468, 528, 468, 528, 488, 512, 484, 512, 484, 496, 496, 528, 468, 524, 472, 528, 468, 528, 464, 532, 464, 532, 464, 532, 2964, 3004, 8932, 532, 1460, 532, 464, 528, 468, 528, 468, 528, 464, 528, 468, 528, 492, 512, 484, 496, 496, 500, 1488, 528, 468, 528, 468, 532, 464, 532, 464, 528, 1460, 532, 1456, 532, 464, 532, 1460, 528, 1464, 528, 1460, 528, 1484, 456, 1536, 500, 1488, 528, 1464, 528, 1460, 532, 464, 532, 464, 532, 464, 528, 1460, 532, 1460, 528, 1460, 528, 472, 524, 468, 528, 492, 512, 484, 452, 540, 500, 1488, 528, 472, 524, 468, 528, 468, 528, 1460, 532, 1460, 528, 468, 528, 1460, 528, 1464, 528, 468, 524, 472, 524, 492, 512, 484, 452, 544, 452, 544, 496, 496, 524, 1464, 532, 1460, 528, 1460, 532, 1460, 528};

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
