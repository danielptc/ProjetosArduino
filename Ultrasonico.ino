long distancia;  //Declaramos uma variavel long para armazenar o valor da distancia
long tiempo;     //Declaramos outra variavel long para armazenar o valor do tempo de resposta

void setup(){
  Serial.begin(9600);  //Iniciamos a comunicação serial
  pinMode(9, OUTPUT);  //Declaramos o pino 9 como saída para a pulsação ultrasónica
  pinMode(8, INPUT);   //Declaramos o pino 8 como entrada para receber o ressalto da pulsação
}

void loop(){
  digitalWrite(9,LOW);      //Apagamos a pulsação ultrasónica
  delayMicroseconds(5);     //Pequena pausa de estabilização
  digitalWrite(9, HIGH);    //Envio da pulsação ultrasónica
  delayMicroseconds(10);    //Pequena pausa de estabilização
  tempo = pulseIn(8, HIGH);    //Função para medir o tempo que decorreu entre o envío da pulsação ultrasónico e quando o sensor recebe o ressalto
  distancia= int(0.017*tiempo); //Fórmula para calcular a distancia usando a velocidade do som como constante
   Serial.print("Distancia "); Serial.print(distancia);  Serial.println(" cm");  //Sacamos o resultado pelo monitor serial
  delay(1000);     //Pequena pausa antes de reiniciar o ciclo
}
