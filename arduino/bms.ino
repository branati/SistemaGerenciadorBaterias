
/*
Universidade de Brasilia - PPMEC
BMS LiFePO4
Autor: Renato Cunha Morais de Freitas


*/

#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x3F); 

int mostra_json = 1;
int segundo = 0;
int tempo = 0;

int i;


// Define the number of samples to keep track of.  The higher the number,
// the more the readings will be smoothed, but the slower the output will
// respond to the input.  Using a constant rather than a normal variable lets
// use this value to determine the size of the readings array.
const int numReadings = 5;
const int numReadings2 = 5;
const int numReadings3 = 5;
const int numReadings4 = 5;
const int numReadings5 = 5;
const int numReadings6 = 5;
const int numReadings7 = 5;
const int numReadings8 = 5;
const int numReadings9 = 5;

float readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
float total = 0;                  // the running total
float average = 0;                // the average


float readings2[numReadings2];      // the readings from the analog input
int readIndex2 = 0;              // the index of the current reading
float total2 = 0;                  // the running total
float average2 = 0;                // the average

float readings3[numReadings3];      // the readings from the analog input
int readIndex3 = 0;              // the index of the current reading
float total3 = 0;                  // the running total
float average3 = 0;                // the average

float readings4[numReadings4];      // the readings from the analog input
int readIndex4 = 0;              // the index of the current reading
float total4 = 0;                  // the running total
float average4 = 0;                // the average

float readings5[numReadings5];      // the readings from the analog input
int readIndex5 = 0;              // the index of the current reading
float total5 = 0;                  // the running total
float average5 = 0;                // the average

float readings6[numReadings6];      // the readings from the analog input
int readIndex6 = 0;              // the index of the current reading
float total6 = 0;                  // the running total
float average6 = 0;                // the average

float readings7[numReadings7];      // the readings from the analog input
int readIndex7 = 0;              // the index of the current reading
float total7 = 0;                  // the running total
float average7 = 0;                // the average

float readings8[numReadings8];      // the readings from the analog input
int readIndex8 = 0;              // the index of the current reading
float total8 = 0;                  // the running total
float average8 = 0;                // the average

float readings9[numReadings9];      // the readings from the analog input
int readIndex9 = 0;              // the index of the current reading
float total9 = 0;                  // the running total
float average9 = 0;                // the average

int inputPin = A8;
int inputPin2 = A1;
int inputPin3 = A2;
int inputPin4 = A3;
int inputPin5 = A4;
int inputPin6 = A5;
int inputPin7 = A6;
int inputPin8 = A7;
int inputPin9 = A0; //sem uso pin A0 com defeito
//-----menu lcd-----
int inputPin10 = A10; //menu
int inputPin11 = A11; //select
int inputPin12 = A12; // move direita
int inputPin13 = A13; // move esquerda
//------------------
int outPin = 9;
int outPin2 = 10; 
int outPin3 = 11; 
int outPin4 = 12; 

//-----Potencia----------
int outPin5 = 8;

//---------- menu lcd----------
int show;
int timeshow;
int qtmenu = 3; //--0 = 1 opcao, 1 = 2 opcoes ...
int potencia = 0;
String txt = "Desligada";
//------------------------------
//---------VCHG-----------------
float vcell1 = 4.2;
float vcell2 = 4.2;
float vcell3 = 4.2;
float vcell4 = 4.2;
float vcellmin = 3.3;
float vcellmax = 4.2;

//---------Controle de Carga-----------
float vcell_referencia = 4.2;
float Kp = 1.8; // Controle de ganho proporcional do Controlador PI de tensao de carga
float Kp_max = 5; // Controle de ganho maximo
float Ki = 0.8; // Controle de integral do Controlador PI de tensao de cerga
int tempo_de_analise_da_carga = 120; //120 = 60 segundos (o loop e de 500ms)
int tempo_de_carga = 0; //Tempo carregando ---- Utilizado para o controle PI
//-------------------------------------

// -----Controle de Corrente-------------
float Ki_2 = 0.1; // Controle Integral do Controlador PI de corrente de carga
float acellmin = 0.05; // Corrente minima para carga das celulas
//---------------------------------------




/* ---------VALOR NO PWM / VOLTS no PWM ------
//int valorpwmarray[] = {171,174,180,185,190,195,200,205,210,215};

int voltspwmarray[10] = {33,34,35,36,37,38,39,40,41,42};

int valorpwmarray[50];

int valorpwmvalortensao(float tensao){
  //tensao = round(tensao*10)/10;
  tensao = (tensao * 10);
  int tensaointeiro = (int)tensao;
  //tensao = round(tensao);

  int valorpwm;
  float valorquebrado;
  
  for (i = 0; i++; i<=10){
    if (tensaointeiro == voltspwmarray[i]){
      valorpwm = valorpwmarray[i];  
    }
  }
    Serial.print("-----"); Serial.print(String(valorpwm)); Serial.println("-------");
  return valorpwm;
}

*/

int valorpwmarray[100];

void setup() {

// ---------VALOR NO PWM / VOLTS no PWM -- Tabela de Referencia ------  
valorpwmarray[33] = {171};
valorpwmarray[34] = {174};
valorpwmarray[35] = {180};
valorpwmarray[36] = {185};
valorpwmarray[37] = {190};
valorpwmarray[38] = {195};
valorpwmarray[39] = {200};
valorpwmarray[40] = {205};
valorpwmarray[41] = {210};
valorpwmarray[42] = {215};
valorpwmarray[43] = {218};
valorpwmarray[44] = {221};
valorpwmarray[45] = {224};
valorpwmarray[46] = {227};
valorpwmarray[47] = {230};
valorpwmarray[48] = {233};
valorpwmarray[49] = {236};
valorpwmarray[50] = {239};

//----------------------------------------------


  
  int error;
  // initialize serial communication with computer:
  Serial.begin(9600);
  Serial.println("LCD...");

  //while (! Serial);

  Serial.println("Checando LCD");

  // See http://playground.arduino.cc/Main/I2cScanner
  Wire.begin();
  Wire.beginTransmission(0x3F);
  error = Wire.endTransmission();
  Serial.print("Error: ");
  Serial.print(error);

  if (error == 0) {
    Serial.println(": LCD detectado.");

  } else {
    Serial.println(": LCD inexistente.");
  } // if

  lcd.begin(16, 2); // initialize the lcd
  show = 0;

  lcd.setBacklight(255);
  lcd.home(); lcd.clear();

  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  for (int thisReading2 = 0; thisReading2 < numReadings2; thisReading2++) {
    readings2[thisReading2] = 0;
  }

  for (int thisReading3 = 0; thisReading3 < numReadings3; thisReading3++) {
    readings3[thisReading3] = 0;
  }

  for (int thisReading4 = 0; thisReading4 < numReadings4; thisReading4++) {
    readings4[thisReading4] = 0;
  }

  for (int thisReading5 = 0; thisReading5 < numReadings5; thisReading5++) {
    readings5[thisReading5] = 0;
  }

  for (int thisReading6 = 0; thisReading6 < numReadings6; thisReading6++) {
    readings6[thisReading6] = 0;
  }

  for (int thisReading7 = 0; thisReading7 < numReadings7; thisReading7++) {
    readings7[thisReading7] = 0;
  }

  for (int thisReading8 = 0; thisReading8 < numReadings8; thisReading8++) {
    readings8[thisReading8] = 0;
  }

    for (int thisReading9 = 0; thisReading9 < numReadings9; thisReading9++) {
    readings8[thisReading9] = 0;
  }

  // -------- Inicio do JSON----------------------
  Serial.println("PPMEC - UNB");  
  Serial.println("Autor: Renato Cunha Morais de Freitas");
  Serial.println("Email: renato@branati.com.br");
  Serial.println("Formato dos dados: JSON. Nao se esqueca de ascrescentar \"]}\" no final do arquivo ao salvar para ter um JSON valido.");
  Serial.println("{");
  Serial.println("\t \"cell\":[");

  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("BMS LiFePO4");
  lcd.setCursor(2,1);
  lcd.print("UNB - PPMEC");
  delay(3000);
  lcd.clear();
  lcd.print("Inicializando ..");
  delay(3000);




}

float mapfloat(long x, long in_min, long in_max, long out_min, long out_max)
{
 return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

float tensao(float valor) {
    float tensao = mapfloat(valor, 0, 1023, 0, 5); 
    return tensao; 
  }

float corrente(float valor) {
    float corrente = mapfloat(valor, 0, 1023, -20, 20); 
    return corrente; 
  }

// -------------------------Controle Propocional Integral 1----------------------------
float erro_anterior[5];
float controle_proporcionalintegral(int numerocelula, float Kp, float vcell_setpoint, float valor_tensao_cell){
  float erro = (vcell_setpoint - valor_tensao_cell);
  if (erro != 0){
    float c_proporcional = Kp * erro; // Controle Proporcional
    float c_integral = (Ki * erro_anterior[numerocelula]); // Controle Integral
    //Serial.print(Ki) ; Serial.print("//") ; Serial.print(erro); Serial.print("//") ; Serial.print(valor_tensao_cell); Serial.print("//") ; Serial.println(erro_anterior);
    
    erro_anterior[numerocelula] = erro;
    float controle_pi = c_proporcional + c_integral + valor_tensao_cell;
    if (controle_pi < 3.3){
      controle_pi = 3.3;
    }
    //Serial.print(c_proporcional); Serial.print("//"); Serial.print(c_integral); Serial.print("//");Serial.print(valor_tensao_cell) ; Serial.print("////////////="); Serial.println(controle_pi) ;

    return controle_pi;
    
  }
}
//-----------------------------------------------------------------------------------

//-----------------Controle Propocional Integral de Corrente de Carga------------------------
float controle_propocionalintegral2(float Kp, float acell_setpoint, float valor_corrente_cell){
  float erro = acell_setpoint - valor_corrente_cell;

  if (erro != 0){
    float c_proporcional = Kp * erro; // Controle Proporcional
    float c_integral = (Ki_2 * erro) * (i / 2);

    float controle_pi = c_proporcional + c_integral;
    
    //----Se controle_pi for maior que a tensao minima de carga entao
    // permite carga, senao a bateria encontra-se carregada
    
    if (controle_pi > acellmin){
      return 1;
    }
    else{
      return 0;
    }
  }
}
//-----------------------------------------------------------------------------------

//--------------------------Controle por percentual-----------somente para testes------
float controlepwmsaida_percentual(float Kp, float vcell_referencia, float valor_tensao_cell){
  float saida_pwm;
  
  if ((valor_tensao_cell != 0) && (Kp != 0)){
    saida_pwm = valor_tensao_cell + (valor_tensao_cell * Kp);
    if (saida_pwm < vcellmin) {
      return vcellmin;
    }
    else if (saida_pwm < vcellmax){
      return saida_pwm;
    }
    else if (valor_tensao_cell >= 42) {
      return vcellmax;
    }
    else if (saida_pwm > 50){
      return 50;
    }

    else{
      
      return saida_pwm;  // return vcellmax = com protecao / return saida_pwm = sem protecao
    }
  } 
}
//--------------------------------------------------------------------------------



//---------------------------Funcao que aplica o controle--------------------------------------------
void controlatensao(int numerocelula, int pin, float tensaocelula){
   int valorcelula = (int)(controle_proporcionalintegral(numerocelula, Kp, vcell_referencia, tensao(tensaocelula)) * 10);
   //float ctlpi = controle_proporcionalintegral(numerocelula, Kp, vcell_referencia, tensao(tensaocelula));
   int valorpwm;
   
   
   if (valorcelula < 33){
    valorcelula = 33;
   }
   
   if (valorcelula > 50){
    valorcelula = 50;
   }

  //Serial.print("//////////");Serial.print(valorcelula); Serial.println("/////////");
   valorpwm = valorpwmarray[valorcelula];
   //Serial.print("//////////");Serial.print(valorpwm);Serial.println("/////////");
   analogWrite(pin, valorpwm);

}
//-------------------------------------------------------------------------------------------------

void controlapotencia(int ligadesliga){
  if (ligadesliga == 1){
    analogWrite(outPin5, 255);
}
  else if (ligadesliga == 0){
    analogWrite(outPin5, 0);
  }
}


int menu = 0;

int selecionado = 0;  

int contador_tempo_teste_carga = 115; // 115 para efetuar primeiro teste
int testando_carga;
int tempo_analisando_carga;

  
void loop() {


  i = i + 1;

  
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(inputPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }


   // subtract the last reading:
  total2 = total2 - readings2[readIndex2];
  // read from the sensor:
  readings2[readIndex2] = analogRead(inputPin2);
  // add the reading to the total:
  total2 = total2 + readings2[readIndex2];
  // advance to the next position in the array:
  readIndex2 = readIndex2 + 1;

  // if we're at the end of the array...
  if (readIndex2 >= numReadings2) {
    // ...wrap around to the beginning:
    readIndex2 = 0;  
  }

  
   // subtract the last reading:
  total3 = total3 - readings3[readIndex3];
  // read from the sensor:
  readings3[readIndex3] = analogRead(inputPin3);
  // add the reading to the total:
  total3 = total3 + readings3[readIndex3];
  // advance to the next position in the array:
  readIndex3 = readIndex3 + 1;

  // if we're at the end of the array...
  if (readIndex3 >= numReadings3) {
    // ...wrap around to the beginning:
    readIndex3 = 0;  
  }

  
   // subtract the last reading:
  total4 = total4 - readings4[readIndex4];
  // read from the sensor:
  readings4[readIndex4] = analogRead(inputPin4);
  // add the reading to the total:
  total4 = total4 + readings4[readIndex4];
  // advance to the next position in the array:
  readIndex4 = readIndex4 + 1;

  // if we're at the end of the array...
  if (readIndex4 >= numReadings4) {
    // ...wrap around to the beginning:
    readIndex4 = 0;  
  }

   // subtract the last reading:
  total5 = total5 - readings5[readIndex5];
  // read from the sensor:
  readings5[readIndex5] = analogRead(inputPin5);
  // add the reading to the total:
  total5 = total5 + readings5[readIndex5];
  // advance to the next position in the array:
  readIndex5 = readIndex5 + 1;

  // if we're at the end of the array...
  if (readIndex5 >= numReadings5) {
    // ...wrap around to the beginning:
    readIndex5 = 0;  
  }

   // subtract the last reading:
  total6 = total6 - readings6[readIndex6];
  // read from the sensor:
  readings6[readIndex6] = analogRead(inputPin6);
  // add the reading to the total:
  total6 = total6 + readings6[readIndex6];
  // advance to the next position in the array:
  readIndex6 = readIndex6 + 1;

  // if we're at the end of the array...
  if (readIndex6 >= numReadings6) {
    // ...wrap around to the beginning:
    readIndex6 = 0;  
  }

   // subtract the last reading:
  total7 = total7 - readings7[readIndex7];
  // read from the sensor:
  readings7[readIndex7] = analogRead(inputPin7);
  // add the reading to the total:
  total7 = total7 + readings7[readIndex7];
  // advance to the next position in the array:
  readIndex7 = readIndex7 + 1;

  // if we're at the end of the array...
  if (readIndex7 >= numReadings7) {
    // ...wrap around to the beginning:
    readIndex7 = 0;  
  }

   // subtract the last reading:
  total8 = total8 - readings8[readIndex8];
  // read from the sensor:
  readings8[readIndex8] = analogRead(inputPin8);
  // add the reading to the total:
  total8 = total8 + readings8[readIndex8];
  // advance to the next position in the array:
  readIndex8 = readIndex8 + 1;

  // if we're at the end of the array...
  if (readIndex8 >= numReadings8) {
    // ...wrap around to the beginning:
    readIndex8 = 0;  
  }

  // subtract the last reading:
  total9 = total9 - readings9[readIndex9];
  // read from the sensor:
  readings9[readIndex9] = analogRead(inputPin9);
  // add the reading to the total:
  total9 = total9 + readings9[readIndex9];
  // advance to the next position in the array:
  readIndex9 = readIndex9 + 1;

  // if we're at the end of the array...
  if (readIndex9 >= numReadings9) {
    // ...wrap around to the beginning:
    readIndex9 = 0;  
  }



  // calculate the average:
  average = total / numReadings;
  average2 = total2 / numReadings2;
  average3 = total3 / numReadings3;
  average4 = total4 / numReadings4;
  average5 = total5 / numReadings5;
  average6 = total6 / numReadings6;
  average7 = total7 / numReadings7;
  average8 = total8 / numReadings8;
  average9 = total9 / numReadings9;

        /* -------- Executa na primeira vez------------------
     if (contador_tempo_teste_carga == 0){
        int i_primeiro_teste;
        while (i_primeiro_teste <= 10){
          controlatensao(outPin, average);
          controlatensao(outPin2, average2);
          controlatensao(outPin3, average3);
          controlatensao(outPin4, average4);
          i_primeiro_teste++;
        }
     }

     */

/*
  if (i == 10){
    int val1 = mapfloat(average, 0, 1023, 0, 255);
    analogWrite(outPin, val1);
    vcell1 = mapfloat(average, 0, 1023, 0, 5);
     
    int val2 = mapfloat(average2, 0, 1023, 0, 255);
    analogWrite(outPin2, val2);
    vcell2 = mapfloat(average2, 0, 1023, 0, 5);

    int val3 = mapfloat(average3, 0, 1023, 0, 255);
    analogWrite(outPin3, val3);
    vcell3 = mapfloat(average3, 0, 1023, 0, 5);

    int val4 = mapfloat(average4, 0, 1023, 0, 255);
    analogWrite(outPin4, val4);
    vcell4 = mapfloat(average4, 0, 1023, 0, 5);
  }
*/

  
  // -----------------LCD ------------------
    if (analogRead(inputPin10) >= 700){
      show = show + 1;
      timeshow= 60000;
    //lcd.setBacklight(0);
    //delay(400);
    //lcd.setBacklight(255);
    if( show > qtmenu ) {
      show = 0;
    }

  }


  if (show == 0){
    lcd.clear();
    lcd.print("V");
    lcd.setCursor(1,0);
    lcd.print(String(tensao(average)));
    
    lcd.setCursor(4,0);
    lcd.print("|");
    lcd.setCursor(5,0);
    lcd.print(String(tensao(average2)));
  
    lcd.setCursor(8,0);
    lcd.print("|");
    lcd.setCursor(9,0);
    lcd.print(String(tensao(average3)));
  
    lcd.setCursor(12,0);
    lcd.print("|");
    lcd.setCursor(13,0);
    lcd.print(String(tensao(average4)));
    
  
    // -----------------LCD MOSTRA AMPERAGEM---------------
    lcd.setCursor(0,1);
    lcd.print("A");
    lcd.print(String((corrente(average5))));
    //lcd.print(analogRead(inputPin11));
    lcd.setCursor(4,1);
    lcd.print("|");
    lcd.setCursor(5,1);
    lcd.print(String((corrente(average6))));
  
    lcd.setCursor(8,1);
    lcd.print("|");
    lcd.setCursor(9,1);
    lcd.print(String((corrente(average7))));
  
    lcd.setCursor(12,1);
    lcd.print("|");
    lcd.setCursor(13,1);
    lcd.print(String((corrente(average8))));
  }
  else if (show == 1){
    lcd.clear();
    float ttotal = tensao(average) + tensao(average2) + tensao(average3) + tensao(average4);
    lcd.print("V SoC:"); lcd.println(String(ttotal));
    lcd.setCursor(0,1);
    float curr = corrente(average9);
    lcd.print("A SoC:"); lcd.println(String(curr));
    
  }
  else if (show == 2){
    lcd.clear();
    lcd.print("Status Potencia:");
    lcd.setCursor(0,1);
      if ((analogRead(inputPin11) >= 700) && (show == 2)){
        if (potencia == 1){
          potencia = 0;
          txt = "Desligada";
          tempo_de_carga = 0;
          controlapotencia(0);
        }
        else if (potencia == 0){
          potencia = 1;
          txt = "Ligada";
          //lcd.print("aa");
          controlapotencia(1);
        }
      }
    lcd.print(txt);
  }
  else if (show == 3){
    //lcd.setCursor(3,1);
    //lcd.cursor();

     //-------------MENU FATOR DE CARGA------------------------------- 
      lcd.clear();
      lcd.print("Fator Proporcional:");
      lcd.setCursor(0,1);
      lcd.print(String(Kp));
      lcd.cursor();
      
      if (analogRead(inputPin11) >= 700){
        selecionado = selecionado + 1;
        while (selecionado == 2){
          lcd.blink();
          if (analogRead(inputPin12) >= 700){
            if (Kp <= Kp_max){
              Kp = Kp + 0.001;
              lcd.setCursor(0,1);
              lcd.print(String(Kp));
              lcd.setCursor(0,1);
            }
          }
          if (analogRead(inputPin13) >= 700){
            if (Kp >= 0.1){
              Kp = Kp - 0.001;
              lcd.setCursor(0,1);
              lcd.print(String(Kp));
              lcd.setCursor(0,1);
            }
          }
        
          if (analogRead(inputPin10) >= 700){
            lcd.cursor();
            lcd.noBlink();
            selecionado = selecionado - 1;
            
            int valorcelula = (int)(vcell1 * 10);
            int valorpwm;
            valorpwm = valorpwmarray[valorcelula];

            //analogWrite(outPin, valorpwm);
            lcd.noCursor();
            break;
          }
          
        }

        if (analogRead(inputPin12) >= 700){
          menu = menu + 1;
          //lcd.cursor();
          //break;     
        }
               
      }
      if (analogRead(inputPin10) >= 700){
        //lcd.setCursor(3,1);
        //lcd.cursor();
        menu = 0;
        lcd.noCursor();
        selecionado = 0;
        //break;
        
      }

      // seta portas digitais para mesmas tensoes que leem em a0 a a3

  }

   segundo = i % 2; 
   if (mostra_json == 1 && (segundo == 0)){
   segundo = 0; 
   tempo = tempo + 1;
   Serial.println("\t {");
   Serial.println("\t \t \"id\":\"01\",");
   Serial.print("\t \t \"time\":\""); Serial.print(tempo); Serial.println("\",");
   Serial.print("\t \t \"tensao\":\""); Serial.print(tensao(average)); Serial.println("\",");
   Serial.print("\t \t \"corrente\":\""); Serial.print(corrente(average5)); Serial.println("\"");
   Serial.println("\t },");

   Serial.println("\t {");
   Serial.println("\t \t \"id\":\"02\",");
   Serial.print("\t \t \"time\":\""); Serial.print(tempo); Serial.println("\",");
   Serial.print("\t \t \"tensao\":\""); Serial.print(tensao(average2)); Serial.println("\",");
   Serial.print("\t \t \"corrente\":\""); Serial.print(corrente(average6)); Serial.println("\"");
   Serial.println("\t },");

   Serial.println("\t {");
   Serial.println("\t \t \"id\":\"03\",");
   Serial.print("\t \t \"time\":\""); Serial.print(tempo); Serial.println("\",");
   Serial.print("\t \t \"tensao\":\""); Serial.print(tensao(average3)); Serial.println("\",");
   Serial.print("\t \t \"corrente\":\""); Serial.print(corrente(average7)); Serial.println("\"");
   Serial.println("\t },");

   Serial.println("\t {");
   Serial.println("\t \t \"id\":\"04\",");
   Serial.print("\t \t \"time\":\""); Serial.print(tempo); Serial.println("\",");
   Serial.print("\t \t \"tensao\":\""); Serial.print(tensao(average4)); Serial.println("\",");
   Serial.print("\t \t \"corrente\":\""); Serial.print(corrente(average8)); Serial.println("\"");
   Serial.println("\t },");
   }

   
 
  delay(500);        // delay in between reads for stability
  
  if (timeshow <= 0){
    //show = 0;
  }
  else{
    timeshow = timeshow - 1000;
  }
// ------------ Para a carga, mede as baterias, aplica o Kp e retorna a carregar ----------------------------
  if ( potencia == 1) {
    contador_tempo_teste_carga = contador_tempo_teste_carga + 1;
    tempo_de_carga = tempo_de_carga + 1;
  }

  if ( contador_tempo_teste_carga == tempo_de_analise_da_carga || testando_carga == 1 || tempo_de_carga == 1 ){
    contador_tempo_teste_carga = 0;
    if (testando_carga == 0){
    potencia = 0;
    controlapotencia(0); // Desliga Potencia
    testando_carga = 1;
    }
    else {
    tempo_analisando_carga = tempo_analisando_carga + 1;
    controlatensao(1,outPin, average);
    controlatensao(2,outPin2, average2);
    controlatensao(3,outPin3, average3);
    controlatensao(4,outPin4, average4);
    }
    if (tempo_analisando_carga >= 10){
      potencia = 1;
      controlapotencia(1); // Liga Potencia
      testando_carga = 0;
      tempo_analisando_carga = 0;  
    }
    
  }
//----------------------------------------------------------------------------------------------------------------


  
}

