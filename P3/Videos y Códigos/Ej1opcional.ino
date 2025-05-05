int leds[] = {13, 12, 11, 10};  // Pines de los LEDs
int numLeds = 4;                // Número total de LEDs

void setup() {
  for (int i = 0; i < numLeds; i++) {
    pinMode(leds[i], OUTPUT);  // Configurar cada pin como salida
  }
}

void loop() {
  // Encender LEDs de izquierda a derecha
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(leds[i], HIGH);
    delay(300);
    digitalWrite(leds[i], LOW);
  }

  // Encender LEDs de derecha a izquierda
  for (int i = numLeds - 2; i > 0; i--) {
    digitalWrite(leds[i], HIGH);
    delay(300);
    digitalWrite(leds[i], LOW);
  }
}
