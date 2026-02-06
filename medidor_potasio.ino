/*
  Medidor experimental de Potasio (K+) con Arduino y LM358
Dispositivo experimental para medir potasio utilizando un Amplificador Operacional LM358 para el acondicionamiento de señal, siguiendo la lógica de la instrumentación analítica real.
Autor: Paulina Juich
  Licencia: 
Este proyecto fue desarrollado por Paulina Juich y registrado en la DNDA (Argentina) bajo el número de expediente EX-2025-78014687- el 18 de Julio de 2025.

Todo el contenido de este repositorio (código fuente, diseño electrónico, documentación) se encuentra protegido por derechos de autor.

⚠️ El incumplimiento de estas condiciones podrá derivar en acciones legales conforme a la Ley 11.723 de Propiedad Intelectual.

© 2025 Paulina Juich. Todos los derechos reservados.

Este diseño, documentación y código están protegidos por la legislación de propiedad intelectual. 

🧠 El uso personal, académico o educativo sin fines de lucro está permitido con atribución.
💰 Cualquier uso comercial, distribución, modificación o integración en productos requiere una licencia paga o autorización expresa.

Contacto para licencias: paulinajuich4@gmail.com

*/

#include <LiquidCrystal.h>

// ---------- PINES ----------
const int analogPin = A0;
const int buttonPin = 2;

// LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// ---------- VARIABLES ----------
bool mode = 0; // 0 = Medición, 1 = Calibración
bool lastButtonState = HIGH;

float voltage = 0.0;
float potassium = 0.0;

// ---------- SETUP ----------
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Medidor K+");
  lcd.setCursor(0, 1);
  lcd.print("Proyecto Hugo");

  delay(2000);
  lcd.clear();
}

// ---------- LOOP ----------
void loop() {
  bool buttonState = digitalRead(buttonPin);

  // Cambio de modo con botón
  if (lastButtonState == HIGH && buttonState == LOW) {
    mode = !mode;
    lcd.clear();
    delay(300);
  }
  lastButtonState = buttonState;

  // Lectura ADC
  int raw = analogRead(analogPin);
  voltage = raw * (5.0 / 1023.0);

  // Modelo SIMULADO de potasio (mmol/L)
  potassium = (2.0 * voltage) - 0.5;

  // límites de seguridad
  if (potassium < 0) potassium = 0;

  // Mostrar según modo
  if (mode == 0) {
    mostrarPotasio(potassium);
  } else {
    mostrarCalibracion(raw, voltage);
  }

  delay(500);
}

// ---------- FUNCIONES ----------
void mostrarPotasio(float k) {
  lcd.setCursor(0, 0);
  lcd.print("Potasio K+     ");

  lcd.setCursor(0, 1);
  lcd.print(k, 2);
  lcd.print(" mmol/L       ");
}

void mostrarCalibracion(int raw, float v) {
  lcd.setCursor(0, 0);
  lcd.print("ADC: ");
  lcd.print(raw);
  lcd.print("     ");

  lcd.setCursor(0, 1);
  lcd.print("V: ");
  lcd.print(v, 2);
  lcd.print(" V      ");
}
