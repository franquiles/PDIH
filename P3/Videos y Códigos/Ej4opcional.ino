#include <Servo.h>  // Incluir la librería para controlar el servomotor

Servo miServo;             // Crear un objeto servo
int botonPin = 7;          // Pin donde está conectado el pulsador
int estadoBoton = 0;       // Variable para guardar el estado del botón

void setup() {
  miServo.attach(9);       // Conectar el servo al pin 9
  pinMode(botonPin, INPUT); // Configurar el pin del botón como entrada
}

void loop() {
  estadoBoton = digitalRead(botonPin); // Leer el estado del botón

  if (estadoBoton == HIGH) {
    miServo.write(90);    // Girar el servo a 90° si se pulsa el botón
  } else {
    miServo.write(0);     // Volver a 0° si no se pulsa
  }

  delay(100);  // Esperar un poco para evitar lecturas erráticas
}
