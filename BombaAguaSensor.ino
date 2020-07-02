
 int ledPin = 3; // pino do led
 int analogPin = 0; // pino para leitura do potenciômetro
 int val = 0; //variável para armazenar o valor lido
 int temp = 0;
 
 void setup()
 { 
  Serial.begin(9600);
    pinMode(ledPin, OUTPUT); // configura pino como saída
 }
 
 void loop()
 {
    val = analogRead(analogPin);  // le o valor analógico  
    temp = (val / 4);

    if(temp >= 230){
      analogWrite(ledPin,LOW);
    }
    else if((temp <= 241) && (temp >= 210)){
      analogWrite(ledPin,70);
    }
    else if((temp <= 209) && (temp >= 150)){
      analogWrite(ledPin,temp);
    }
    else{
      analogWrite(ledPin,255);
    }
    
        
   Serial.println(val / 4);
   delay(500);

}
