#include <Servo.h>      //Inclue biblioteca do servo motor
#include <Ultrasonic.h> //Inclue a biblioteca do sensor ultrassonico

int motor1 = 10;    //direita trás
int motor2 = 11;    //direta frente
int motor3 = 8;    //esquerda trás
int motor4 = 9;    //esquerda frente
int sensor1 = 7;  //pino para receber o sinal do fototransistor
int sensor2 = 6;  //pino para receber o sinal do fototransistor

Servo myservo;

const int trigPin = 3;  //Pino trig do ultrassonico
const int echoPin = 4;  //Pino echo do ultrassonico
long duration;          //Variavel usado no calculo de distancia
int distance;           //Variavel onde armazena a distancia
int VerificarEsquerda;  //Variavel para armazenar o valor da distancia na esquerda a ser comparado com a da direita
int VerificarDireita;   //Variavel para armazenar o valor da distancia na direita a ser comparado com a da esquerda

int buzzer = 2;

void setup(){
  myservo.attach(5);    //Define o pino 5 para usar o servo
  
  pinMode(motor1, OUTPUT);  //definindo o pino do LED como saída
  pinMode(motor2, OUTPUT);  //definindo o pino do LED como saída
  pinMode(motor3, OUTPUT);  //definindo o pino do LED como saída
  pinMode(motor4, OUTPUT);  //definindo o pino do LED como saída
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, HIGH);
 Serial.begin(9600);

 }

void frente()
{
  digitalWrite(motor2,HIGH);
  digitalWrite(motor4,HIGH);
  digitalWrite(motor1,LOW);
  digitalWrite(motor3,LOW);
}
void tras()
{
  digitalWrite(motor1,HIGH);
  digitalWrite(motor3,HIGH);
  digitalWrite(motor2,LOW);
  digitalWrite(motor4,LOW);
}
void esquerda()
{
  digitalWrite(motor2,HIGH);
  digitalWrite(motor3,HIGH);
  digitalWrite(motor1,LOW);
  digitalWrite(motor4,LOW);
}
void direita()
{
  digitalWrite(motor1,HIGH);
  digitalWrite(motor4,HIGH);
  digitalWrite(motor2,LOW);
  digitalWrite(motor3,LOW);
}
void para()
{
  digitalWrite(motor1,LOW);
  digitalWrite(motor4,LOW);
  digitalWrite(motor2,LOW);
  digitalWrite(motor3,LOW);
}


void ultrassonic(){
  digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
}
 
void loop() {
  
ultrassonic();

if (distance <= 50){
  para();
  digitalWrite(buzzer, LOW);
  tras();
  delay(500);
  ultrassonic();
  para();
  digitalWrite(buzzer, HIGH);
  
  myservo.write(180);
  ultrassonic();
  VerificarEsquerda = distance;
  digitalWrite(buzzer, LOW);
  delay(800);
  digitalWrite(buzzer, HIGH);
  delay(200);
  
  myservo.write(0);
  ultrassonic();
  VerificarDireita = distance;  
  digitalWrite(buzzer, LOW);
  delay(800);
  digitalWrite(buzzer, HIGH);
  delay(200);

    if (VerificarEsquerda > VerificarDireita){
      
      esquerda();
      delay(700);
      frente();
    }

    else if (VerificarEsquerda == VerificarDireita){
      para();
    }
  
    else{
      direita();
      delay(700);
      frente();
  }  
  myservo.write(90);
  
}

else{
  myservo.write(90);
  frente();
}
}  
