int LED = 13;
char leituraSerial;
 
void setup() {
  Serial.begin(9600); //Inicia serial 
  pinMode(LED, OUTPUT); //led como saida
}
 
void loop() {
  //Se chegar dado da serial, avaliamos e comandamos.
  if(Serial.available() > 0){
    leituraSerial = (char) Serial.read();
    //Foi a letra 'a'? Acende o led.
    if(leituraSerial == 'a'){
      digitalWrite(LED,HIGH);
    }
    //Foi a letra 'd'? Apaga o led.
    if(leituraSerial == 'd'){
      digitalWrite(LED,LOW);
    }
  }

}
