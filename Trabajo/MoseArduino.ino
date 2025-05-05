#define PINBT 2
#define PINLED 13

#define TSHORT 200
#define TLONG 300
#define TLONGE 1000

#define LETTER_TIMEOUT 2000
#define WORD_TIMEOUT 5000

bool btPressed = false;
unsigned long lastPressed = 0;
unsigned long lastInputTime = 0;

String morseBuffer = "";
String palabraActual = "";
String fraseCompleta = "";

bool esperandoConfirmacion = false;
bool modoSeleccionado = false;
int modo = 0; // 1 = botón, 2 = texto

void setup() {
  pinMode(PINBT, INPUT_PULLUP);
  pinMode(PINLED, OUTPUT);
  Serial.begin(9600);
  delay(1000); // tiempo para que se abra el Monitor Serie
  mostrarMenu();
}

void loop() {
  if (!modoSeleccionado) {
    if (Serial.available()) {
      String entrada = Serial.readStringUntil('\n');
      entrada.trim();
      if (entrada == "1") {
        modo = 1;
        modoSeleccionado = true;
        Serial.println("Modo 1: escribir con el boton.");
      } else if (entrada == "2") {
        modo = 2;
        modoSeleccionado = true;
        Serial.println("Modo 2: escribe una palabra y la mostrare en Morse con el LED.");
        Serial.println("Escribe la palabra:");
      } else {
        Serial.println("Opción no valida. Escribe 1 o 2.");
      }
    }
    return;
  }

  // MODO 1: escribir pulsando
  if (modo == 1) {
    modoBoton();
  }

  // MODO 2: escribir palabra por teclado
  if (modo == 2) {
    if (Serial.available()) {
      String palabra = Serial.readStringUntil('\n');
      palabra.trim();
      Serial.print("Mostrando en Morse: ");
      Serial.println(palabra);
      reproducirMorse(palabra);
      Serial.println("Finalizado.");
      mostrarMenu(); // volver al menú
      modoSeleccionado = false;
    }
  }
}

// Función que gestiona el MODO BOTÓN
void modoBoton() {
  unsigned long now = millis();
  btPressed = !digitalRead(PINBT);

  if (btPressed && lastPressed == 0) {
    lastPressed = now;
    digitalWrite(PINLED, HIGH);
  }

  if (!btPressed && lastPressed != 0) {
    unsigned long duration = now - lastPressed;
    digitalWrite(PINLED, LOW);
    lastPressed = 0;

    if (esperandoConfirmacion) {
      if (duration <= TSHORT) {
        Serial.println("CONTINUAR");
        esperandoConfirmacion = false;
      } else if (duration >= TLONG && duration <= TLONGE) {
        Serial.println("TERMINAR");
        Serial.print("Frase completa: ");
        Serial.println(fraseCompleta);
        Serial.println("-------------------");
        fraseCompleta = "";
        esperandoConfirmacion = false;
      }
      return;
    }

    if (duration <= TSHORT) {
      morseBuffer += ".";
      Serial.print(".");
    } else if (duration >= TLONG && duration <= TLONGE) {
      morseBuffer += "-";
      Serial.print("-");
    } else {
      Serial.print("(Ignorado)");
    }

    lastInputTime = now;
  }

  if (morseBuffer.length() > 0 && now - lastInputTime > LETTER_TIMEOUT) {
    char letra = morseToChar(morseBuffer);
    Serial.print(" Letra: ");
    Serial.println(letra);
    palabraActual += letra;
    morseBuffer = "";
  }

  if (palabraActual.length() > 0 && now - lastInputTime > WORD_TIMEOUT) {
    Serial.print("Palabra completa: ");
    Serial.println(palabraActual);
    fraseCompleta += palabraActual + " ";
    palabraActual = "";
    esperandoConfirmacion = true;
    Serial.println("¿Seguir escribiendo?");
    Serial.println("Pulsa punto para CONTINUAR, raya para TERMINAR.");
  }
}

// Función que reproduce palabra en Morse con el LED
void reproducirMorse(String palabra) {
  palabra.toUpperCase();
  for (int i = 0; i < palabra.length(); i++) {
    char letra = palabra[i];
    if (letra == ' ') {
      delay(1500); // espacio entre palabras
      continue;
    }

    String morse = charToMorse(letra);
    for (int j = 0; j < morse.length(); j++) {
      if (morse[j] == '.') {
        digitalWrite(PINLED, HIGH);
        delay(400);
        digitalWrite(PINLED, LOW);
      } else if (morse[j] == '-') {
        digitalWrite(PINLED, HIGH);
        delay(1000);
        digitalWrite(PINLED, LOW);
      }
      delay(400); // espacio entre símbolos
    }
    delay(800); // espacio entre letras
  }
}

// Mostrar menú al inicio
void mostrarMenu() {
  Serial.println("Selecciona modo:");
  Serial.println("1 - Escribir con el boton");
  Serial.println("2 - Escribir palabra desde teclado");
  Serial.print("Escribe tu eleccion: ");
}

// Traducción de código morse a letra
char morseToChar(String code) {
  if (code == ".-") return 'A';   if (code == "-...") return 'B';
  if (code == "-.-.") return 'C'; if (code == "-..") return 'D';
  if (code == ".") return 'E';    if (code == "..-.") return 'F';
  if (code == "--.") return 'G';  if (code == "....") return 'H';
  if (code == "..") return 'I';   if (code == ".---") return 'J';
  if (code == "-.-") return 'K';  if (code == ".-..") return 'L';
  if (code == "--") return 'M';   if (code == "-.") return 'N';
  if (code == "---") return 'O';  if (code == ".--.") return 'P';
  if (code == "--.-") return 'Q'; if (code == ".-.") return 'R';
  if (code == "...") return 'S';  if (code == "-") return 'T';
  if (code == "..-") return 'U';  if (code == "...-") return 'V';
  if (code == ".--") return 'W';  if (code == "-..-") return 'X';
  if (code == "-.--") return 'Y'; if (code == "--..") return 'Z';
  return '?';
}

// Traducción de letra a morse
String charToMorse(char c) {
  switch (c) {
    case 'A': return ".-";   case 'B': return "-...";
    case 'C': return "-.-."; case 'D': return "-..";
    case 'E': return ".";    case 'F': return "..-.";
    case 'G': return "--.";  case 'H': return "....";
    case 'I': return "..";   case 'J': return ".---";
    case 'K': return "-.-";  case 'L': return ".-..";
    case 'M': return "--";   case 'N': return "-.";
    case 'O': return "---";  case 'P': return ".--.";
    case 'Q': return "--.-"; case 'R': return ".-.";
    case 'S': return "...";  case 'T': return "-";
    case 'U': return "..-";  case 'V': return "...-";
    case 'W': return ".--";  case 'X': return "-..-";
    case 'Y': return "-.--"; case 'Z': return "--..";
    default: return "";
  }
}
