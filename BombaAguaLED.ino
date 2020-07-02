  
// Projeto : Controle de luminosidade de led com LDR  
// Autor : Arduino e Cia  
   
//int pinoled = 10; //Pino ligado ao anodo do led  
int pinopot = 0;  //Pino ligado ao LDR  
int valorpot = 0; //Armazena valor lido do LDR, entre 0 e 1023  
float luminosidade = 0; //Valor de luminosidade do led  

int led01 = 4;
int led02 = 5;
int led03 = 6;
int led04 = 7;
int led05 = 8;
int led06 = 9;
int led07 = 10;
   
void setup()  
{  
  Serial.begin(9600);    //Inicializa a serial  
  pinMode(led01, OUTPUT); //Define o pino do led como saída 
  pinMode(led02, OUTPUT);
  pinMode(led03, OUTPUT);
  pinMode(led04, OUTPUT);
  pinMode(led05, OUTPUT);
  pinMode(led06, OUTPUT);
  pinMode(led07, OUTPUT);
   
  pinMode(pinopot, INPUT);  //Define o pino do LDR como entrada  
}  
   
void loop()  
{  
  // Le o valor - analogico - do LDR  
  valorpot = analogRead(pinopot);  

  // Converte o valor lido do LDR
  luminosidade = map(valorpot, 1023, 0, 0, 255); 
  
  // Mostra o valor da luminosidade no monitor serial  
  Serial.println(luminosidade); 


    if(luminosidade <= 40){
      digitalWrite(led01,HIGH);
      digitalWrite(led02,LOW);
      digitalWrite(led03,LOW);
      digitalWrite(led04,LOW);
      digitalWrite(led05,LOW);
      digitalWrite(led06,LOW);
      digitalWrite(led07,LOW);
      
    }
    else if((luminosidade >= 41) && (luminosidade <= 50)){
      digitalWrite(led01,HIGH);
      digitalWrite(led02,HIGH);
      digitalWrite(led03,LOW);
      digitalWrite(led04,LOW);
      digitalWrite(led05,LOW);
      digitalWrite(led06,LOW);
      digitalWrite(led07,LOW);
    }

    else if((luminosidade >= 51) && (luminosidade <= 60)){
      digitalWrite(led01,HIGH);
      digitalWrite(led02,HIGH);
      digitalWrite(led03,HIGH);
      digitalWrite(led04,LOW);
      digitalWrite(led05,LOW);
      digitalWrite(led06,LOW);
      digitalWrite(led07,LOW);
    }

    
    else if((luminosidade >= 61) && (luminosidade <= 70)){
      digitalWrite(led01,HIGH);
      digitalWrite(led02,HIGH);
      digitalWrite(led03,HIGH);
      digitalWrite(led04,HIGH);
      digitalWrite(led05,LOW);
      digitalWrite(led06,LOW);
      digitalWrite(led07,LOW);
    }

    else if((luminosidade >= 71) && (luminosidade <= 80)){
      digitalWrite(led01,HIGH);
      digitalWrite(led02,HIGH);
      digitalWrite(led03,HIGH);
      digitalWrite(led04,HIGH);
      digitalWrite(led05,HIGH);
      digitalWrite(led06,LOW);
      digitalWrite(led07,LOW);
    }

    else if((luminosidade >= 81) && (luminosidade <= 90)){
      digitalWrite(led01,HIGH);
      digitalWrite(led02,HIGH);
      digitalWrite(led03,HIGH);
      digitalWrite(led04,HIGH);
      digitalWrite(led05,HIGH);
      digitalWrite(led06,HIGH);
      digitalWrite(led07,LOW);
    }
    
    else{
      digitalWrite(led01,HIGH);
      digitalWrite(led02,HIGH);
      digitalWrite(led03,HIGH);
      digitalWrite(led04,HIGH);
      digitalWrite(led05,HIGH);
      digitalWrite(led06,HIGH);
      digitalWrite(led07,HIGH);
    }

  delay(500);
 } 
