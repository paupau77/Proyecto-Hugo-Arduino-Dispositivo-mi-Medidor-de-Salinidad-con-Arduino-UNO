/*
 Proyecto Hugo - Medidor de Salinidad Básico con Arduino UNO
  -------------------------------------------
  Dispositivo básico para medir la conductividad eléctrica de una muestra líquida 
  (simulada con un potenciómetro), mostrando en pantalla LCD 16x2 I2C el voltaje, 
  valor ADC y una estimación simple de la conductividad. 
  Está preparado para incorporar una fórmula profesional que convierta la 
  conductividad a salinidad real (g/L, ppt, etc).

  Autora: Paulina Juich
  Licencia: 
  Este proyecto fue desarrollado por Paulina Juich y registrado en la DNDA (Argentina) 
  bajo el número de expediente EX-2025-78014687- el 18 de Julio de 2025.

  Todo el contenido de este repositorio (código fuente, diseño electrónico, documentación) 
  se encuentra protegido por derechos de autor.

  ⚠️ El incumplimiento de estas condiciones podrá derivar en acciones legales 
  conforme a la Ley 11.723 de Propiedad Intelectual.

  © 2025 Paulina Juich. Todos los derechos reservados.

  🧠 El uso personal, académico o educativo sin fines de lucro está permitido con atribución.
  💰 Cualquier uso comercial, distribución, modificación o integración en productos requiere 
     una licencia paga o autorización expresa.

  Contacto para licencias: paulinajuich4@gmail.com

  Mejoras en este código:
  - Sensor de conductividad (A0)
  - Sensor de temperatura LM35 (A1)
  - Módulo pH analógico / potenciómetro (A2)
  - LCD 16x2 I2C
  - Botón con INPUT_PULLUP

  Autor: Paulina Juich
  © 2025 - Todos los derechos reservados
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// ================= PINES =================
const int pinConductividad = A0;   // Sensor de conductividad (potenciómetro)
const int pinTemperatura   = A1;   // LM35
const int pinPH            = A2;   // Sensor pH o potenciómetro
const int buttonPin        = 2;

// ================= PARÁMETROS =================
float maxConductividad = 50.0;     // mS/cm (ajustable)
const float TEMP_REF = 25.0;       // °C
const float ALFA = 0.02;           // coeficiente térmico
const float K_PH = 0.15;           // coeficiente corrección pH

// ================= ESTADO =================
bool medirActivo = true;
bool botonPresionado = false;

// ================= FÓRMULAS =================
float a1 = 0.5,  b1 = 0.8;
float a2 = 0.02, b2 = 0.4, c2 = 0.7;
float a3 = 0.001, b3 = -0.02, c3 = 0.5, d3 = 0.6;

int tipoFormula = 3;

unsigned long ultimaLectura = 0;
const unsigned long intervaloLectura = 300;

// ================= SETUP =================
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
  Serial.println("Medidor de Salinidad con compensacion");

  lcd.setCursor(0, 0);
  lcd.print("Medidor Salinidad");
  lcd.setCursor(0, 1);
  lcd.print("Inicializando...");
  delay(2000);
  lcd.clear();
}

// ================= LOOP =================
void loop() {
  leerBoton();

  if (medirActivo && (millis() - ultimaLectura >= intervaloLectura)) {

    // --- LECTURAS ---
    int adcCond = analogRead(pinConductividad);
    int adcTemp = analogRead(pinTemperatura);
    int adcPH   = analogRead(pinPH);

    float voltCond = adcCond * (5.0 / 1023.0);
    float voltTemp = adcTemp * (5.0 / 1023.0);
    float voltPH   = adcPH   * (5.0 / 1023.0);

    // --- CONVERSIONES ---
    float temperatura = voltTemp * 100.0;              // LM35
    float conductividad = (adcCond / 1023.0) * maxConductividad;
    float pH = voltPH * 3.5;                            // aproximación típica

    // --- COMPENSACIONES ---
    float condTempComp = conductividad / (1 + ALFA * (temperatura - TEMP_REF));
    float factorPH = exp(K_PH * abs(pH - 7.0));
    float condFinal = condTempComp * factorPH;

    // --- SALINIDAD ---
    float salinidad = 0.0;
    if (tipoFormula == 1) {
      salinidad = a1 * condFinal + b1;
    } else if (tipoFormula == 2) {
      salinidad = a2 * pow(condFinal, 2) + b2 * condFinal + c2;
    } else {
      salinidad = a3 * pow(condFinal, 3) +
                  b3 * pow(condFinal, 2) +
                  c3 * condFinal + d3;
    }

    mostrarLectura(condFinal, salinidad, temperatura, pH);

    // --- SERIAL ---
    Serial.print("Temp: "); Serial.print(temperatura, 1); Serial.print(" C | ");
    Serial.print("pH: "); Serial.print(pH, 2); Serial.print(" | ");
    Serial.print("Cond: "); Serial.print(condFinal, 2); Serial.print(" mS/cm | ");
    Serial.print("Sal: "); Serial.print(salinidad, 2); Serial.println(" g/L");

    ultimaLectura = millis();
  }
}

// ================= BOTÓN =================
void leerBoton() {
  static unsigned long lastDebounceTime = 0;
  const unsigned long debounceDelay = 50;

  bool estado = digitalRead(buttonPin) == LOW;

  if (estado && !botonPresionado && (millis() - lastDebounceTime > debounceDelay)) {
    botonPresionado = true;
    medirActivo = !medirActivo;
    lcd.clear();
    lastDebounceTime = millis();
  }

  if (!estado && botonPresionado) {
    botonPresionado = false;
    lastDebounceTime = millis();
  }
}

// ================= LCD =================
void mostrarLectura(float cond, float sal, float temp, float ph) {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("C:");
  lcd.print(cond, 1);
  lcd.print(" T:");
  lcd.print(temp, 0);

  lcd.setCursor(0, 1);
  lcd.print("S:");
  lcd.print(sal, 1);
  lcd.print(" pH:");
  lcd.print(ph, 1);
}
