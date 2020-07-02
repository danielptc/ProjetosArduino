//Sensor de temperatura usando o LM35
 
int LM35 = A0; // Define o pino que lera a saída do LM35
int temperatura; // Variável que armazenará a temperatura medida
 
//Função que será executada uma vez quando ligar ou resetar o Arduino
void setup() {
Serial.begin(9600); // inicializa a comunicação serial
}
 
//Função que será executada continuamente
void loop() {
temperatura = int((float(analogRead(LM35))*5/(1023))/0.01);
//Serial.print("Temperatura: ");
Serial.println(temperatura);
delay(500);
}
