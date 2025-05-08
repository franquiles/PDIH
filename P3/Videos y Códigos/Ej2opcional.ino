const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 8;

long duracion;
int distancia;

void setup() {
  pinMode(trigPin, OUTPUT);  // TRIG como salida
  pinMode(echoPin, INPUT);   // ECHO como entrada
  pinMode(buzzer, OUTPUT);   // Buzzer como salida

  Serial.begin(9600);       
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracion = pulseIn(echoPin, HIGH);

  distancia = duracion * 0.034 / 2;

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  if (distancia < 10) {
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
  }

  delay(200);
}
