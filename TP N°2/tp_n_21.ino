#define LED_R 9
#define LED_G 10
#define LED_B 11

#define POT_TIEMPO A0
#define POT_R A1
#define POT_G A2
#define POT_B A3

#define BOTON 2
#define BUZZER 6

bool sistemaActivo = true;
bool estadoBotonAnterior = HIGH;

unsigned long tiempoCambio = 0;
unsigned long ultimoCambio = 0;

int estadoColor = 0;

void setup() {

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  pinMode(BOTON, INPUT_PULLUP);

  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  bool estadoBoton = digitalRead(BOTON);

  if (estadoBotonAnterior == HIGH && estadoBoton == LOW) {

    sistemaActivo = !sistemaActivo;

    delay(50);
  }

  estadoBotonAnterior = estadoBoton;

  if (sistemaActivo) {

    int lecturaTiempo = analogRead(POT_TIEMPO);

    tiempoCambio = (lecturaTiempo * 3000.0) / 1023.0;

    int valorR = (analogRead(POT_R) * 255.0) / 1023.0;
    int valorG = (analogRead(POT_G) * 255.0) / 1023.0;
    int valorB = (analogRead(POT_B) * 255.0) / 1023.0;

    if (millis() - ultimoCambio >= tiempoCambio) {

      ultimoCambio = millis();

      analogWrite(LED_R, 0);
      analogWrite(LED_G, 0);
      analogWrite(LED_B, 0);

      for (int i = 0; i < 3; i++) {

        digitalWrite(LED_R, HIGH);
        digitalWrite(LED_G, HIGH);
        digitalWrite(LED_B, HIGH);

        delay(100);

        digitalWrite(LED_R, LOW);
        digitalWrite(LED_G, LOW);
        digitalWrite(LED_B, LOW);

        delay(100);
      }

      tone(BUZZER, 1000, 200);

      if (estadoColor == 0) {

        analogWrite(LED_R, valorR);
        analogWrite(LED_G, 0);
        analogWrite(LED_B, 0);

      } else if (estadoColor == 1) {

        analogWrite(LED_R, 0);
        analogWrite(LED_G, valorG);
        analogWrite(LED_B, 0);

      } else {

        analogWrite(LED_R, 0);
        analogWrite(LED_G, 0);
        analogWrite(LED_B, valorB);
      }

      estadoColor++;

      if (estadoColor > 2) {
        estadoColor = 0;
      }

      Serial.print("Tiempo: ");
      Serial.print(tiempoCambio / 1000.0);
      Serial.println(" s");

      Serial.print("R: ");
      Serial.println(valorR);

      Serial.print("G: ");
      Serial.println(valorG);

      Serial.print("B: ");
      Serial.println(valorB);

      Serial.println("-");
    }
  }
}