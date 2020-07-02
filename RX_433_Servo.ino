#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();
int pos = 0;
#include <Servo.h>

Servo Servo01;
Servo Servo02;

#define ledVerdeServo01 8
#define ledVermelhoServo01 7
#define ledVerdeServo02 6
#define ledVermelhoServo02 5

void setup() {
    Serial.begin(9600);
    
    Servo01.attach(9); 
    Servo02.attach(10); 
    
    mySwitch.enableReceive(0);

    pinMode(ledVerdeServo01, OUTPUT);
    pinMode(ledVermelhoServo01, OUTPUT);
    pinMode(ledVerdeServo02, OUTPUT);
    pinMode(ledVermelhoServo02, OUTPUT);



}
void loop() {
    if (mySwitch.available()) {
        int value = mySwitch.getReceivedValue();
        if (value > 0) {
            if (mySwitch.getReceivedValue()==1){
              Servo01.write(40); 

              digitalWrite(ledVerdeServo01, HIGH);
              digitalWrite(ledVermelhoServo01, LOW);
              
              delay(1000);
              
              Servo01.write(90);
              
              }
              
            else if (mySwitch.getReceivedValue()==2){
              Servo01.write(140); 
              
              digitalWrite(ledVermelhoServo01, HIGH);
              digitalWrite(ledVerdeServo01, LOW);
              
              delay(1000);
              
              Servo01.write(90);

              }

              else if (mySwitch.getReceivedValue()==3){
              Servo02.write(40); 
              
              digitalWrite(ledVerdeServo02, LOW);
              digitalWrite(ledVermelhoServo02, HIGH);
              
              delay(1000);
              
              Servo02.write(90);


              }

              else if (mySwitch.getReceivedValue()==4){
              Servo02.write(140); 
              
              digitalWrite(ledVermelhoServo02, LOW);
              digitalWrite(ledVerdeServo02, HIGH);
              
              delay(1000);
              
              Servo02.write(90);

              }

              else if (mySwitch.getReceivedValue()==5){
              Servo01.write(40); 
              Servo02.write(140); 

              digitalWrite(ledVerdeServo01, HIGH);
              digitalWrite(ledVerdeServo02, LOW);
              digitalWrite(ledVermelhoServo01, LOW);
              digitalWrite(ledVermelhoServo02, HIGH);
              
              delay(1000);
              
              Servo01.write(90);
              Servo02.write(90);          
             

              }
              

              else if (mySwitch.getReceivedValue()==6){
              Servo01.write(140); 
              Servo02.write(40);

              digitalWrite(ledVerdeServo01, LOW);
              digitalWrite(ledVerdeServo02, HIGH);
              digitalWrite(ledVermelhoServo01, HIGH);
              digitalWrite(ledVermelhoServo02, LOW);
               
              delay(1000);
              
              Servo01.write(90);
              Servo02.write(90);              


              }              

        }
        mySwitch.resetAvailable();
    }
}
