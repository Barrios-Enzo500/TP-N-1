#include <Adafruit_NeoPixel.h>

#define PIN_LED 6
#define NUM_LEDS 12

#define POT A0
#define BOTON 2

Adafruit_NeoPixel ring(NUM_LEDS, PIN_LED, NEO_GRB + NEO_KHZ800);

int efecto = 0;
bool estadoAnterior = HIGH;

void setup() {
  ring.begin();
  ring.show();

  pinMode(BOTON, INPUT_PULLUP);
}

void loop() {

  bool estadoBoton = digitalRead(BOTON);

  if (estadoAnterior == HIGH && estadoBoton == LOW) {
    efecto++;
    if (efecto > 2) efecto = 0;
    apagarTodo();
    delay(200);
  }

  estadoAnterior = estadoBoton;

  switch (efecto) {
    case 0:
      efecto1();
      break;

    case 1:
      efecto2();
      break;

    case 2:
      efecto3();
      break;
  }
}

int velocidad() {
  return map(analogRead(POT), 0, 1023, 50, 1000);
}

void apagarTodo() {
  ring.clear();
  ring.show();
}

void efecto1() {

  uint32_t colores[] = {
    ring.Color(255,0,0),
    ring.Color(0,255,0),  
    ring.Color(0,0,255),   
    ring.Color(255,255,0),
    ring.Color(255,0,255),  
    ring.Color(0,255,255)  
  };

  for(int i=0; i<NUM_LEDS; i++) {

    apagarTodo();

    ring.setPixelColor(i, colores[i % 6]);
    ring.show();

    delay(velocidad());
  }

  delay(1000);
}

void efecto2() {

  for(int i=0; i<NUM_LEDS; i++) {

    apagarTodo();

    ring.setPixelColor(i, ring.Color(0,255,0));
    ring.show();

    delay(velocidad());
  }

  for(int i=NUM_LEDS-1; i>=0; i--) {

    apagarTodo();

    ring.setPixelColor(i, ring.Color(255,0,0));
    ring.show();

    delay(velocidad());
  }

  delay(1000);
}

void efecto3() {

  uint32_t color1 = ring.Color(random(256), random(256), random(256));
  uint32_t color2 = ring.Color(random(256), random(256), random(256));

  apagarTodo();

  for(int i=0; i<NUM_LEDS; i+=2) {
    ring.setPixelColor(i, color1);
  }

  ring.show();
  delay(velocidad());

  apagarTodo();

  for(int i=1; i<NUM_LEDS; i+=2) {
    ring.setPixelColor(i, color2);
  }

  ring.show();
  delay(velocidad());

  apagarTodo();

  delay(1000);
}