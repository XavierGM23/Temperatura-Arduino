// INTERRUPCIONES Y SERIALCOMUNICATION


#include <LiquidCrystal.h>

int TEMP_NORMAL = 20;

int SENSOR_TEMP = A0;

int BTN_INCREMENTO = 22;
int BTN_DECREMENTO = 24;

int LED_TEMP_NORMAL = 26;
int LED_ATENTION = 28;
int LED_DANGER = 30;

int RELE_SIGNAL_1 = 32;
int RELE_SIGNAL_2 = 34;

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int signalVoltage, TEMP_CONTROL;
int lecturaBtnInc, lecturaBtnDec;

int eatadoLedNormal, estadoLedAtention, estadoLedDanger;

byte flechas[8] = {
  B00100,
  B01110,
  B11111,
  B00000,
  B00000,
  B11111,
  B01110, 
  B00100,
};

void printLCD(int tempSet,int tempActual) {
  lcd.setCursor(0,0);
  lcd.print("T.Set: ");
  lcd.print(tempSet);
  lcd.print((char)223);
  lcd.print("C ");
  lcd.write((byte)0);
  
  lcd.setCursor(0,1);
  lcd.print("T.Act: ");
  lcd.print(tempActual);
  lcd.print((char)223);
  lcd.print("C");  
}


void setup() {

  pinMode(BTN_INCREMENTO, INPUT);
  pinMode(BTN_DECREMENTO, INPUT);

  pinMode(LED_TEMP_NORMAL, OUTPUT);
  pinMode(LED_ATENTION, OUTPUT);
  pinMode(LED_DANGER, OUTPUT);
  pinMode(RELE_SIGNAL_1, OUTPUT);
  pinMode(RELE_SIGNAL_2, OUTPUT);

  lcd.begin(16,2);

  lcd.createChar(0, flechas);

  Serial.begin(9600);

}

void loop() {

  lecturaBtnInc = digitalRead(BTN_INCREMENTO);

  if (lecturaBtnInc) {
    delay(100);
    while(!lecturaBtnInc);
    delay(100);
    TEMP_NORMAL += 1;
  }

  lecturaBtnDec = digitalRead(BTN_DECREMENTO);

  if (lecturaBtnDec) {
    delay(100);
    while(!lecturaBtnDec);
    delay(100);
    TEMP_NORMAL -= 1;
  }

  if (lecturaBtnInc & lecturaBtnDec == HIGH) {
    Serial.println("Presione uno a la vez");
  }


  if (TEMP_NORMAL >= 18 && TEMP_NORMAL < 22) {
    digitalWrite(LED_TEMP_NORMAL, HIGH);
    digitalWrite(LED_ATENTION, LOW);
    digitalWrite(LED_DANGER, LOW);         
  } else if (TEMP_NORMAL >= 22 && TEMP_NORMAL < 24 ) {
    digitalWrite(LED_TEMP_NORMAL, LOW);
    digitalWrite(LED_ATENTION, HIGH);
    digitalWrite(LED_DANGER, LOW);    
  } else if (TEMP_NORMAL >= 24 && TEMP_NORMAL <= 28) {
    digitalWrite(LED_TEMP_NORMAL, LOW);
    digitalWrite(LED_ATENTION, LOW);
    digitalWrite(LED_DANGER, HIGH);    
  } else if (TEMP_NORMAL < 18) {
    TEMP_NORMAL = 18;
  } else if (TEMP_NORMAL > 28) {
    TEMP_NORMAL = 28;
  }
  
  signalVoltage = analogRead(SENSOR_TEMP);

/////////////////////////////////////////////////////////////////
// PARA EL SENSOR LM35
/////////////////////////////////////////////////////////////////
//  TEMP_CONTROL = ((signalVoltage * 5000) / 1023) / 10;

/////////////////////////////////////////////////////////////////
// PARA PRUEBAS CON POTENCIOMETRO
/////////////////////////////////////////////////////////////////
  TEMP_CONTROL = map(signalVoltage, 0 , 1023, 0, 30);

    printLCD(TEMP_NORMAL,TEMP_CONTROL);

  

  if (TEMP_CONTROL < TEMP_NORMAL) { 
    // Horno Encendido y Ventilador Apagado
    digitalWrite(RELE_SIGNAL_1, HIGH);
    digitalWrite(RELE_SIGNAL_2, LOW);
  } else if(TEMP_CONTROL > TEMP_NORMAL) {
    // Horno Apagado y Ventilador Encendido
    digitalWrite(RELE_SIGNAL_1, LOW);
    digitalWrite(RELE_SIGNAL_2, HIGH);
  } else if (TEMP_CONTROL == TEMP_NORMAL) {
    // Horno Apagado y Ventilador Apagado
    digitalWrite(RELE_SIGNAL_1, LOW);
    digitalWrite(RELE_SIGNAL_2, LOW);
  }
  
  Serial.print(TEMP_CONTROL);
  Serial.print(",");
  Serial.print(TEMP_NORMAL);
  Serial.print(",");
  Serial.print(digitalRead(RELE_SIGNAL_1));
  Serial.print(",");
  Serial.print(digitalRead(RELE_SIGNAL_2));
  Serial.print(",");
  Serial.print(digitalRead(LED_TEMP_NORMAL));
  Serial.print(",");
  Serial.print(digitalRead(LED_ATENTION));
  Serial.print(",");
  Serial.println(digitalRead(LED_DANGER));

  delay(250);
}
