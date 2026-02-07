/*
Medidor experimental de Potasio (K+) con Arduino y LM358
Dispositivo experimental para medir potasio utilizando un Amplificador Operacional LM358 
para el acondicionamiento de señal, siguiendo la lógica de la instrumentación analítica real.

Basado en diagrama de circuito: Arduino UNO + LM358 + LCD I2C

Autor: Paulina Juich
Licencia:
Este proyecto fue desarrollado por Paulina Juich y registrado en la DNDA (Argentina) 
bajo el número de expediente EX-2025-78014687- el 18 de Julio de 2025.

Todo el contenido de este repositorio se encuentra protegido por derechos de autor.
⚠️ El incumplimiento de estas condiciones podrá derivar en acciones legales.

© 2025 Paulina Juich. Todos los derechos reservados.
Contacto para licencias: paulinajuich4@gmail.com
*/

#include <Wire.h>              // Librería para comunicación I2C
#include <LiquidCrystal_I2C.h> // Librería para LCD con adaptador I2C

// ---------- PINES ----------
const int analogPin = A0;      // Entrada desde el LM358 (Filtro RC)
const int buttonPin = 2;       // Botón con resistencia interna Pullup

// ---------- CONFIGURACIÓN LCD I2C ----------
// Dirección I2C: Generalmente es 0x27 o 0x3F. Si no funciona, prueba cambiar a 0x3F.
// Formato: dirección, columnas, filas
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// ---------- VARIABLES ----------
bool pausa = false;       
bool lastButtonState = HIGH; // Estado inicial HIGH por el INPUT_PULLUP

float voltage = 0.0;
float potassium = 0.0;

// ---------- SETUP ----------
void setup() {
  // Configuración del botón según diagrama (Usar INPUT_PULLUP)
  // Esto conecta la resistencia interna, el botón cierra a GND (Pin 2 -> GND)
  pinMode(buttonPin, INPUT_PULLUP);

  // Inicialización del LCD I2C
  lcd.init();       
  lcd.backlight();  // Encender la luz de fondo

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

  // Detectar flanco de bajada (de soltado a presionado)
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    pausa = !pausa; // Alternar estado de pausa

    // Limpiar el indicador de pausa si volvemos a medir
    if (!pausa) {
      lcd.setCursor(11, 0);
      lcd.print("     "); 
    }

    delay(250); // Debounce para evitar rebotes
  }

  // Guardar el estado para la siguiente vuelta
  lastButtonState = currentButtonState;

  // Si NO estamos en pausa, actualizamos la medición
  if (!pausa) {
    // Lectura analógica del pin A0 (Salida del LM358 tras filtro RC)
    int raw = analogRead(analogPin);
    voltage = raw * (5.0 / 1023.0);

    /* Cálculo de concentración de Potasio.
       NOTA: El diagrama muestra un Seguidor de Voltaje con una referencia de 2.5V 
       en el divisor resistivo. Asegúrate de que tu fórmula matemática coincida 
       con la curva de calibración de tu electrodo simulado.
    */
    potassium = (2.0 * voltage) - 0.5;

    // Evitar valores negativos en la pantalla
    if (potassium < 0) potassium = 0;

    lcd.setCursor(0, 1);
    lcd.print(potassium, 2);
    lcd.print(" mmol/L       "); // Espacios extra para limpiar caracteres viejos

  } else {
    // Indicador visual de estado de PAUSA
    lcd.setCursor(11, 0); 
    lcd.print("PAUSA");
  }

  delay(100); // Pequeña espera para estabilidad
}
