void setup() {
  // Configurar los pines de salida para los LEDs
  pinMode(11, OUTPUT); // LED rojo
  pinMode(12, OUTPUT); // LED amarillo
  pinMode(13, OUTPUT); // LED verde
  pinMode(7, INPUT);   // Botón
}

void loop() {
  // Leer el estado del botón (HIGH o LOW)
  int boton = digitalRead(7);

  // Si el botón está presionado (nivel alto)
  if (boton == HIGH) {
    digitalWrite(11, HIGH); // Encender LED rojo
    digitalWrite(12, LOW);  // Apagar LED amarillo
    digitalWrite(13, LOW);  // Apagar LED verde
  }
  else {
    // Si el botón NO está presionado
    digitalWrite(11, LOW);  // Apagar LED rojo
    digitalWrite(12, HIGH); // Encender LED amarillo
    digitalWrite(13, HIGH); // Encender LED verde
  }
}
