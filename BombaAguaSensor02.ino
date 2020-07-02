  
// Projeto : Controle de luminosidade de led com LDR  
// Autor : Arduino e Cia  
   
int pinoled = 10; //Pino ligado ao anodo do led  
int pinopot = 0;  //Pino ligado ao LDR  
int valorpot = 0; //Armazena valor lido do LDR, entre 0 e 1023  
float luminosidade = 0; //Valor de luminosidade do led  
   
void setup()  
{  
  Serial.begin(9600);    //Inicializa a serial  
  pinMode(pinoled, OUTPUT); //Define o pino do led como saída  
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
      analogWrite(pinoled,LOW);
    }
    else if((luminosidade >= 41) && (temp <= 89)){
      analogWrite(pinoled,luminosidade);
    }
    else{
      analogWrite(pinoled,255);
    }

  delay(500);
 } 
