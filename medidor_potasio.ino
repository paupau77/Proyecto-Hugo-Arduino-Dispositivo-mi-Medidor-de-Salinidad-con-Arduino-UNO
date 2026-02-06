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
bool pausa = false;       
bool lastButtonState = HIGH; // Estado anterior del botón

float voltage = 0.0;
float potassium = 0.0;

// ---------- SETUP ----------
void setup() {
  // Usamos INPUT_PULLUP para evitar resistencias externas
  pinMode(buttonPin, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.clear();

  // Pantalla de Inicio
  lcd.setCursor(0, 0);
  lcd.print("Medidor K+");
  lcd.setCursor(0, 1);
  lcd.print("Proyecto Hugo");

  delay(2000);
  lcd.clear();
  
  // Encabezado fijo
  lcd.setCursor(0, 0);
  lcd.print("Potasio K+");
}

// ---------- LOOP ----------
void loop() {
  // Leer el estado del botón (LOW si está presionado, HIGH si no)
  bool currentButtonState = digitalRead(buttonPin);

  // Detectar cuando el botón PASA de NO presionado a PRESIONADO (Flanco de bajada)
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    pausa = !pausa; // Cambiar el estado de pausa
    
    // Limpiar el indicador de pausa si volvemos a medir
    if (!pausa) {
      lcd.setCursor(11, 0);
      lcd.print("     "); 
    }
    
    delay(250); // Debounce para evitar que un solo clic se cuente como dos
  }
  
  // Guardar el estado para la siguiente vuelta del loop
  lastButtonState = currentButtonState;

  // Si NO estamos en pausa, actualizamos la medición
  if (!pausa) {
    int raw = analogRead(analogPin);
    voltage = raw * (5.0 / 1023.0);

    // Modelo de potasio (Asegúrate de ajustar esta fórmula según tu LM358)
    potassium = (2.0 * voltage) - 0.5;

    if (potassium < 0) potassium = 0;

    lcd.setCursor(0, 1);
    lcd.print(potassium, 2);
    lcd.print(" mmol/L       ");
    
  } else {
    // Si estamos en pausa, solo mostramos el texto sin borrar el valor anterior
    lcd.setCursor(11, 0); 
    lcd.print("PAUSA");
  }

  delay(50); // Un delay más corto hace que el botón responda más rápido
}
