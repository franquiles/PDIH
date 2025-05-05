// Código para controlar tres LEDs (rojo, amarillo y verde) con Arduino

void setup() {
  // Configuración de los pines como salidas
  pinMode(11, OUTPUT);  // LED rojo
  pinMode(12, OUTPUT);  // LED amarillo
  pinMode(13, OUTPUT);  // LED verde
}

void loop() {
  // Encender LED rojo y apagar los demás
  digitalWrite(11, HIGH);  // Encender rojo
  digitalWrite(12, LOW);   // Apagar amarillo
  digitalWrite(13, LOW);   // Apagar verde
  delay(1500);             // Esperar 1.5 segundos

  // Encender LED amarillo y apagar los demás
  digitalWrite(11, LOW);   // Apagar rojo
  digitalWrite(12, HIGH);  // Encender amarillo
  digitalWrite(13, LOW);   // Apagar verde
  delay(1500);             // Esperar 1.5 segundos

  // Encender LED verde y apagar los demás
  digitalWrite(11, LOW);   // Apagar rojo
  digitalWrite(12, LOW);   // Apagar amarillo
  digitalWrite(13, HIGH);  // Encender verde
  delay(1500);             // Esperar 1.5 segundos
}
