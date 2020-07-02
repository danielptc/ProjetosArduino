const int pinoPOT = A2; //PINO ANALÓGICO UTILIZADO PELO POTENCIÔMETRO
const int pinoLED = 10; //PINO DIGITAL UTILIZADO PELO LED

float luminosidadeLED = 0; //VARIÁVEL QUE ARMAZENA O VALOR DA LUMINOSIDADE QUE SERÁ APLICADA AO LED

void setup(){
  Serial.begin(9600);
   pinMode(pinoPOT, INPUT); //DEFINE O PINO COMO ENTRADA
   pinMode(pinoLED, OUTPUT); //DEFINE O PINO COMO SAÍDA
}

void loop(){
  luminosidadeLED = map(analogRead(pinoPOT), 0, 1023, 0, 255); //EXECUTA A FUNÇÃO "map" DE ACORDO COM OS PARÂMETROS PASSADOS
  analogWrite(pinoLED, luminosidadeLED); //APLICA AO LED O VALOR DE LUMINOSIDADE GERADO PELA FUNÇÃO "map"
  Serial.println(luminosidadeLED );
  delay(1000);
}
