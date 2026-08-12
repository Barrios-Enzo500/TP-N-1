#include <Adafruit_NeoPixel.h>

#define BOTON 2
#define BUZZER 3
#define DADO1 4
#define DADO2 5

Adafruit_NeoPixel dado1(32, DADO1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel dado2(32, DADO2, NEO_GRB + NEO_KHZ800);

int numeros[6][4] = {
  {0,0,0,1},
  {1,0,0,1},
  {1,0,1,1},
  {1,1,1,1},
  {1,1,0,1},
  {1,1,1,0}
};

bool estadoAnterior = HIGH;

void setup() {

  pinMode(BOTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);

  dado1.begin();
  dado2.begin();

  dado1.show();
  dado2.show();

  randomSeed(analogRead(A0));
}

void loop() {

  bool estadoActual = digitalRead(BOTON);

  if (estadoAnterior == HIGH && estadoActual == LOW) {

    int n1;
    int n2;

    for(int v = 0; v < 15; v++) {

      int aux1 = random(1,7);
      int aux2 = random(1,7);

      dado1.clear();
      dado2.clear();

      for(int tira = 0; tira < 4; tira++) {

        if(numeros[aux1-1][tira] == 1) {

          for(int led = tira * 8; led < (tira * 8) + 8; led++) {
            dado1.setPixelColor(led, dado1.Color(0,0,255));
          }
        }

        if(numeros[aux2-1][tira] == 1) {

          for(int led = tira * 8; led < (tira * 8) + 8; led++) {
            dado2.setPixelColor(led, dado2.Color(0,0,255));
          }
        }
      }

      dado1.show();
      dado2.show();

      delay(80);
    }

    n1 = random(1,7);
    n2 = random(1,7);

    dado1.clear();
    dado2.clear();

    for(int tira = 0; tira < 4; tira++) {

      if(numeros[n1-1][tira] == 1) {

        for(int led = tira * 8; led < (tira * 8) + 8; led++) {
          dado1.setPixelColor(led, dado1.Color(0,255,0));
        }
      }

      if(numeros[n2-1][tira] == 1) {

        for(int led = tira * 8; led < (tira * 8) + 8; led++) {
          dado2.setPixelColor(led, dado2.Color(0,255,0));
        }
      }
    }

    dado1.show();
    dado2.show();

    if(n1 + n2 == 7) {

      for(int k = 0; k < 5; k++) {

        for(int i = 0; i < 32; i++) {
          dado1.setPixelColor(i, dado1.Color(255,0,0));
          dado2.setPixelColor(i, dado2.Color(255,0,0));
        }

        dado1.show();
        dado2.show();

        tone(BUZZER, 500);
        delay(150);

        tone(BUZZER, 1000);
        delay(150);

        tone(BUZZER, 1500);
        delay(150);

        dado1.clear();
        dado2.clear();

        dado1.show();
        dado2.show();

        noTone(BUZZER);
        delay(200);
      }
    }
  }

  estadoAnterior = estadoActual;
}