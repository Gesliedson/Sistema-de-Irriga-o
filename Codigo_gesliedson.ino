// C++ code
//
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(32, 16, 2);

unsigned long tempo_bomba  = millis();
int tempo = 4000;
int bomba = 8; 
int m_espera = 9;
int i_noturna = 7;

int solo = A0;
int soloUmidade;
int lum = A1;
int lumvalor;

void setup()
{
  
  lcd.begin(16,2);
  Serial.begin(9600);
  
  pinMode(bomba, OUTPUT);
  pinMode(m_espera, OUTPUT);
  pinMode(i_noturna, OUTPUT);
  
  pinMode(solo,INPUT);
  pinMode(lum, INPUT);
  
  lcd.init();
    
  lcd.backlight();
  lcd.leftToRight();
  lcd.setCursor(3,0);
  lcd.print("MONITOR DE");
  lcd.setCursor(1,1);
  lcd.print("UMIDADE E LUZ");
  delay(tempo);
   
}

void registros ()
{
  lcd.setCursor(0,0);
  lcd.print("LUZ: ");
  lcd.setCursor(4,0);
  lcd.print(lumvalor);
  lcd.setCursor(7,0);
  lcd.print("%");
  
  lcd.setCursor(0,1);
  lcd.print("UMIDADE: ");
  lcd.setCursor(8,1);
  lcd.print(soloUmidade);
  lcd.setCursor(11,1);
  lcd.print("%");
  
  delay(3000);
  lcd.clear();
  
}

void loop()
{
   
 
	
  
  tempo_bomba  = millis();
  // Sensor de umidade
  soloUmidade = analogRead(solo); 
  soloUmidade = map(soloUmidade, 0,1023 ,0,190);
  //sensor de luminosidade
  lumvalor = analogRead(lum);
  
  lumvalor = map(lumvalor,0, 1017, 150,0);
  //Serial.print(lumvalor);
  //***********************************************//
  
  lcd.clear();
  
  if (soloUmidade < 50 && lumvalor <=45  )
  {
	 digitalWrite(m_espera, LOW);
     digitalWrite(bomba, HIGH);
     digitalWrite(i_noturna, LOW);
     

	 lcd.setCursor(4,0);
     lcd.print("SOLO SECO");
     lcd.setCursor(2,1);
     lcd.print("--IRRIGANDO--");
     delay(tempo);
     lcd.clear();
     
     registros ();
    
  }
  
  else if (soloUmidade >=50)
  {
    digitalWrite(bomba, LOW);

  }
  
  else 
  {
    digitalWrite(bomba, LOW);
  }
  
  if (soloUmidade >= 50 && lumvalor <45)
  {
    digitalWrite(m_espera, HIGH);
    digitalWrite(bomba, LOW);
    digitalWrite(i_noturna, LOW);
    
    lcd.setCursor(3,0);
    lcd.print("IRRIGACAO");
    lcd.setCursor(1,1);
    lcd.print("--COMPLETA--");
    delay (tempo);
    lcd.clear();
    registros ();
  }
  
  else if ( soloUmidade < 50 && lumvalor  > 45)
  {
    digitalWrite(m_espera, LOW);
    digitalWrite(bomba, LOW);
    digitalWrite(i_noturna, HIGH);
    
    lcd.setCursor(6,0);
    lcd.print("LUZ");
    lcd.setCursor(2,1);
    lcd.print("INSUFICIENTE");
    delay (tempo);
    lcd.clear();
    registros ();
  }
  
  else if (soloUmidade >=50 && lumvalor > 45)
  {
    digitalWrite(m_espera, HIGH);
    digitalWrite(bomba, LOW);
    digitalWrite(i_noturna, LOW);
    
    lcd.setCursor(3,0);
    lcd.print("SOLO UMIDO");
    lcd.setCursor(0,1);
    lcd.print("LUZ INSUFICIENTE");
    delay (tempo);
    lcd.clear();
    registros ();
  }
  
 }