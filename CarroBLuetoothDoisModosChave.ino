#include <Servo.h>
#include <Ultrasonic.h>

int motor1 = 10;    //direita trás
int motor2 = 11;    //direta frente
int motor3 = 8;    //esquerda trás
int motor4 = 9;    //esquerda frente
int sensor1 = 7;  //pino para receber o sinal do fototransistor
int sensor2 = 6;  //pino para receber o sinal do fototransistor

Servo myservo;

const int trigPin = 3;
const int echoPin = 4;
long duration;
int distance;     
int VerificarEsquerda;
int VerificarDireita;

int buzzer = 2;

int chave = 12;
int valorChave = 0;

void setup(){
  myservo.attach(5);
  
  pinMode(motor1, OUTPUT);  //definindo o pino do LED como saída
  pinMode(motor2, OUTPUT);  //definindo o pino do LED como saída
  pinMode(motor3, OUTPUT);  //definindo o pino do LED como saída
  pinMode(motor4, OUTPUT);  //definindo o pino do LED como saída
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, HIGH);
  pinMode(chave, INPUT);
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

void obstaculo(){  

   // if(valorChave == LOW){
   
ultrassonic();

if (distance <= 20){
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
   /* }
    else{
      para() ;
      bluetooth();
    }*/
}

void bluetooth(){

  //if(valorChave == HIGH){
   
 if(Serial.available()>0)
   {    
      char data= Serial.read();
      switch(data)
      {
case 'a': frente();break;
case 'b': tras();break;
case 'c': esquerda();break;
case 'h': direita();break;
case 'e':para() ;break;
case 'f':para() ;break;
case 'g':para() ;break;
case 'd':para() ;break;
        default : break;
  digitalWrite(motor2,LOW);
  digitalWrite(motor1,LOW);
  digitalWrite(motor3,LOW);
  digitalWrite(motor4,LOW);
      }
   }
   delay(50);
  
/*}
  else{
    obstaculo();
  }*/
}
 
void loop() {

  valorChave = digitalRead(chave);

  if (valorChave == HIGH){
    
    bluetooth();
    
  }
  else{

    obstaculo();
        
  }
 

}  
