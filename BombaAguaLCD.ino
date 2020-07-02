#include <LiquidCrystal.h>
 
//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int pinSensor = 0;  //Pino ligado ao sensor
int valorpot = 0; //Armazena valor lido do Sensor, entre 0 e 1023  
float temperatura = 0; //Variavel que armazena o valor da temperatura  
float PWM = 0; //Variavel que armazen o valor da PWM
float RPM = 0; //Variavel para calculo do RPM
float xRPM = 0; //Variavel com o valor de RPM
float fluxo = 0;
float xFluxo = 0;
float pump = 0; //Variavel para calculo da % do uso da bomba
float xPump = 0; //Variavel com o valor da % do uso da bomba
float tensao = 0; //Variavel para calculo da tensao
float xTensao = 0; //Variavel com o valor da tensao

int RPM_int = 0; //Variavel que armazena o valor convertido de FLOAT para INT da RPM
int temperatura_int = 0; //Variavel que armazena o valor convertido de FLOAT para INT da Temperatura
int pump_int = 0; //Variavel que armazena o valor convertido de FLOAT para INT da pump (Bomba)
int fluxo_int = 0;

#define buzer 8 //Pino do Buzer
#define bomba 10 // Pino da Bomba
#define chaveDireto 7 //Pino da chave para ligar a bomba de forma direta

int valorChave = 0; //Variavel onde armazena o valor da chave
 
void setup()
{
  //Define o número de colunas e linhas do LCD
  lcd.begin(16, 2);

  pinMode(pinSensor, INPUT);
  pinMode(buzer, OUTPUT);
  pinMode(bomba, OUTPUT);
  pinMode(chaveDireto, INPUT);
}
 
void loop()
{

  valorpot = analogRead(pinSensor); //Valorport recebe o valor da porta analogica do sensor  

  valorChave = digitalRead(chaveDireto);
  

  // Converte o valor lido do LDR
  PWM = map(valorpot, 1023, 0, 0, 255);

  temperatura = PWM;

  
  //CALCULO PARA SABER A TENSAO RELATIVA NA BOMBA DE ACORDO COM A VARIAÇÃO DO SENSOR
  tensao = 12*PWM;  
  xTensao = tensao/255;

  //CALCULO PARA SABER QUANTOD RPM ESTA O MOTOR DA BOMBA
  RPM = xTensao*19500;
  xRPM = RPM/12;

  //CALCULO PARA SABER QUANTOS % A BOMBA ESTA FUNCIONANDO
  pump = PWM*100;
  xPump = pump/255;

  fluxo = 40*xRPM;
  xFluxo = fluxo/19500;

  RPM_int = (int) xRPM; //Converte o valor de FLOAT de XRPM para INT RPM_int
  temperatura_int = (int) temperatura; //Converte o valor de FLOAT de temperatura para INT temperatura_int
  pump_int = (int) xPump;//Converte o valor de FLOAT de xPump para INT pump_int
  fluxo_int = (int) xFluxo;
  
  //Limpa a tela
  lcd.clear();
  //Posiciona o cursor na coluna 0, linha 0;
  lcd.setCursor(0, 0);
  //Envia o texto "CLT:" entre aspas para o LCD
  lcd.print("CLT:");
  //Envia o valor da variavel "temperatura_int" para o LCD
  lcd.print(temperatura_int);
  lcd.print("'C");
  
  //Posiciona o cursor na coluna 10, linha 0;
  lcd.setCursor(10, 0);  
  lcd.print("F:");
  lcd.print(fluxo_int*2);
  lcd.print("L");

  lcd.setCursor(0, 1);  
  lcd.print("RPM:");
  lcd.print(RPM_int*2);

  lcd.setCursor(10, 1);
  lcd.print("P:");
  lcd.print(pump_int*2);
  lcd.print("%");


  
    if(temperatura <= 40) { //Se a temperatura for menor do que 45, o codigo é executado
      if(valorChave == LOW){
      
        lcd.setCursor(10, 0);  
        lcd.print("F:");
        lcd.print("000L");
      
        lcd.setCursor(0, 1);
        lcd.print("RPM:");
        lcd.print("0000");;
      
        lcd.setCursor(10, 1);
        lcd.print("P:");
        lcd.print("000%");

        analogWrite(bomba, LOW); //A bomba é desligada
      }
      else {
        lcd.setCursor(0, 0);  
        lcd.print("CHAVE MANUAL LIGA");
      
        lcd.setCursor(0, 1);
        lcd.print("BOMBA ACIONADA!!");          

        analogWrite(bomba, 255);

    }
    }  

    else if((temperatura >= 41) && (temperatura <= 45)){ 
    }
    
    else if((temperatura >= 46) && (temperatura <= 80)){ //Se a temperatura estiver entre 46 e 85, o codigo é executado
      lcd.setCursor(10, 1);
      lcd.print("P:");
      lcd.print(pump_int*2);
      lcd.print("%");

      analogWrite(bomba, temperatura*2); //A bomba liga e a velocidade do motor é de 
                                         //acordo com a variação de temperatura multiplicado por 2
    }

    else if((temperatura >= 81) && (temperatura <= 85)){ 
    }

    
    else if(temperatura >= 110){ 
      lcd.clear();  
      lcd.setCursor(2, 0);
      lcd.print("ALERTA!!!!!");
      lcd.setCursor(0, 1);
      lcd.print("ALTA TEMPERATURA");

      analogWrite(bomba, 255);
      
      digitalWrite(buzer, HIGH);
      delay(600);
      digitalWrite(buzer, LOW);
      delay(150);
    }


    
    else {
      lcd.setCursor(0, 1);
      lcd.print("RPM:");
      lcd.print("19500");;
      
      lcd.setCursor(10, 1);
      lcd.print("P:");
      lcd.print("100%");

      lcd.setCursor(10, 0);  
      lcd.print("F:");
      lcd.print("100L");

      analogWrite(bomba, 255);

    }

    
  delay(500);
}
