#define TEMP A0
#define PIR 2
#define MOTOR 9
#define LAMPARA 8

float temperatura;
int movimiento;
int pwmMotor;

void setup()
{
  pinMode(PIR, INPUT);
  pinMode(MOTOR, OUTPUT);
  pinMode(LAMPARA, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  int lectura = analogRead(TEMP);
  float voltaje = lectura * (5.0 / 1023.0);
  temperatura = (voltaje - 0.5) * 100;

  movimiento = digitalRead(PIR);

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.print(" °C   Movimiento: ");
  Serial.println(movimiento);

  if (movimiento == HIGH)
    digitalWrite(LAMPARA, HIGH);
  else
    digitalWrite(LAMPARA, LOW);

  if (temperatura <= 15)
  {
    pwmMotor = 50;
  }
  else if (temperatura >= 50)
  {
    pwmMotor = 255;     
  }
  else
  {
    pwmMotor = map((int)temperatura, 15, 50, 50, 255);
  }

  analogWrite(MOTOR, pwmMotor);

  delay(300);
}