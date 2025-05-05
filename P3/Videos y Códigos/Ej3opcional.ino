int sensorPin = A0;      // LDR conectado al pin A0
int ledPin = 9;          // LED conectado al pin 9 (PWM)
int valorLuz = 0;        // Lectura de la luz
int brillo = 0;          // Valor PWM para el LED

void setup() {
  pinMode(ledPin, OUTPUT);     // Configura el pin del LED como salida
  Serial.begin(9600);          // Inicia la comunicación serie
}

void loop() {
  valorLuz = analogRead(sensorPin);              // Leer la luz del LDR
  brillo = map(valorLuz, 0, 1023, 255, 0);        // Convertir la lectura en valor PWM inverso

  analogWrite(ledPin, brillo);                   // Ajustar el brillo del LED

  // Mostrar datos en el monitor serie
  Serial.print("Luz: ");
  Serial.print(valorLuz);
  Serial.print(" → Brillo LED: ");
  Serial.println(brillo);

  delay(100);    // Esperar 100 ms
}
