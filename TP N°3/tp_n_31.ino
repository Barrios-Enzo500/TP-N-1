#include <LiquidCrystal.h>

#define LCD_RS 12
#define LCD_EN 11
#define LCD_D4 4
#define LCD_D5 7
#define LCD_D6 13
#define LCD_D7 A2

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

#define TEMP_PIN A0
#define PIR_PIN 2
#define LDR_PIN A1

#define TRIG_PIN 9
#define ECHO_PIN 10

#define RED_PIN 3
#define GREEN_PIN 5
#define BLUE_PIN 6

#define BUZZER 8

void setup() {

  Serial.begin(9600);

  lcd.begin(16, 2);

  pinMode(PIR_PIN, INPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  pinMode(BUZZER, OUTPUT);
}

void loop() {

  int tempValue = analogRead(TEMP_PIN);

  float voltage = tempValue * 5.0;
  voltage /= 1024.0;

  float temperature = (voltage - 0.5) * 100;

  int motion = digitalRead(PIR_PIN);

  int lightValue = analogRead(LDR_PIN);

  float porcentajeLuz = map(lightValue, 0, 1023, 0, 100);

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);

  float distance = duration * 0.034 / 2;

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature);

  lcd.print(" L:");
  lcd.print((int)porcentajeLuz);

  lcd.setCursor(0, 1);
  lcd.print("D:");
  lcd.print(distance);

  lcd.print("cm");

  Serial.print("Temp: ");
  Serial.print(temperature);

  Serial.print(" Luz: ");
  Serial.print(porcentajeLuz);

  Serial.print("% Distancia: ");
  Serial.print(distance);

  Serial.print(" Movimiento: ");
  Serial.println(motion);

  analogWrite(RED_PIN, 0);
  analogWrite(GREEN_PIN, 0);
  analogWrite(BLUE_PIN, 0);

  noTone(BUZZER);

  bool noche = porcentajeLuz < 20;

  if (temperature > 39) {

    analogWrite(RED_PIN, 255);

    tone(BUZZER, 1000);
    delay(300);
    noTone(BUZZER);

    Serial.println("ALERTA: TOCANDO OBRA");
  }

  else if (motion == HIGH) {

    analogWrite(RED_PIN, 255);
    analogWrite(GREEN_PIN, 150);

    tone(BUZZER, 700);
    delay(200);
    noTone(BUZZER);

    Serial.println("Movimiento detectado");
  }

  if (!noche && distance < 100) {

    analogWrite(RED_PIN, 255);

    tone(BUZZER, 1200);
    delay(150);

    noTone(BUZZER);
    delay(150);

    tone(BUZZER, 1200);
    delay(150);

    noTone(BUZZER);

    Serial.println("PELIGRO: Muy cerca");
  }

  if (noche && (motion == HIGH || temperature > 39)) {

    analogWrite(RED_PIN, 255);

    tone(BUZZER, 1500);

    Serial.println("ALARMA NOCTURNA ACTIVADA");
  }

  delay(1000);
}