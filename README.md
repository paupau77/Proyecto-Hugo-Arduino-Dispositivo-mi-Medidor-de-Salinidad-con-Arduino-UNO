# Proyecto Hugo - Medidor experimental de Potasio (K+) con Arduino y LM358

![Arduino](https://img.shields.io/badge/Arduino-UNO-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Electrónica](https://img.shields.io/badge/Electrónica-Analog-FA7343?style=for-the-badge&logoColor=white)
![Simulator](https://img.shields.io/badge/Wokwi%20%26%20Tinkercad-Online-1ABC9C?style=for-the-badge&logo=tinkercad&logoColor=white)
![LCD 16x2](https://img.shields.io/badge/LCD-16x2-1E90FF?style=for-the-badge)
![LM358](https://img.shields.io/badge/OpAmp-LM358-yellow?style=for-the-badge)
![Proyecto Activo](https://img.shields.io/badge/Estado-Activo-brightgreen?style=for-the-badge)
![En Desarrollo](https://img.shields.io/badge/Estado-En%20Desarrollo-yellow?style=for-the-badge)
![Licencia DNDA](https://img.shields.io/badge/Licencia-DNDA-orange?style=for-the-badge)

> Este proyecto es un **medidor de potasio (K+) experimental basado en Arduino UNO**. Está orientado a aplicaciones educativas y de prototipado, utilizando un **Amplificador Operacional LM358** para el acondicionamiento de señal, siguiendo la lógica de la instrumentación analítica real.
> 
> Está **documentado con detalle, modular, abierto a mejoras, y hecho con un profundo sentido humano y compromiso social**.
> NO constituye un dispositivo médico ni realiza diagnósticos clínicos.
> Este proyecto fue creado con mucho ❤️ para ayudar en el monitoreo de salud, química y biología.

---

## Dedicatoria 💚

Este proyecto está dedicado **en memoria de Hugo Passucci**, una de las dos inspiraciones humanas de este proyecto.

Su figura estuvo presente como referencia de valores que atraviesan todo el desarrollo del dispositivo: el cuidado, la voluntad, la búsqueda de ayudar a los demás y el compromiso con lo humano detrás de lo técnico. Nombrar este proyecto con su nombre es una forma de reconocer esa inspiración y darle continuidad a la huella que dejó.

---

## 📋 Índice del Proyecto


### ** 1. 📖 Presentación del Proyecto

* **1.1 Descripción general
* **1.2 Alcance y advertencias
* **1.3 Dedicatoria
  
### ** 2. ⚙️ Hardware y Componentes

* **2.1 Lista de componentes
* **2.2 Esquema de conexión
* **2.3 Simulación en Tinkercad y Wokwi
* **2.4 Acondicionamiento de señal con LM358
  
### ** 3. 🧠 Funcionamiento del Sistema

* **3.1 Principio de medición
* **3.2 Modelo matemático
* **3.3 Modos de funcionamiento
* **3.4 Flujo general del sistema
  
### ** 4. 💻 Desarrollo del Software
* **4.1 Librerías utilizadas
* **4.2 Variables y estructura
* **4.3 Configuración (setup)
* **4.4 Ciclo principal (loop)
* **4.5 Fragmentos de código destacados

### ** 5. 📚 Documentación Técnica
* **5.1 Archivos complementarios
* **5.2 Verificación en simuladores
* **5.3 Fichas técnicas

### ** 6. 💖 Sentido Humano del Proyecto

* **6.1 Por qué medir potasio
* **6.2 Historia personal
* **6.3 Impacto social
* **6.4 Democratización de la medición

### ** 7. 🌍 Valor e Importancia del Dispositivo

* **7.1 Aplicaciones prácticas
* **7.2 Uso educativo y científico
* **7.3 Proyección futura

### ** 8. ❤️ Agradecimientos

* **8.1 Familia y entorno
* **8.2 Amistades
* **8.3 Docentes y acompañantes

### ** 9. 🙌 Créditos

* **9.1 Profesor Sergio Conde
* **9.2 Colaboraciones especiales

### ** 10. 📄 Licencia y Derechos

* **10.1 Registro DNDA
* **10.2 Condiciones de uso

### ** 11. ✍️ Autora

* **11.1 Formación
* **11.2 Trayectoria

### ** 12. 🌟 Nota Final
---

## 🔧 Componentes

| Componente | Cantidad | Descripción |
| :--- | :---: | :--- |
| **Arduino UNO** | 1 | Microcontrolador principal |
| **LM358 (Op-Amp)** | 1 | Acondicionador de señal del electrodo |
| **LCD 16x2** | 1 | Visualización de datos (pines 7, 8, 9, 10, 11, 12) |
| **Potenciómetro 10k** | 1 | Simulación de Electrodo K+ |
| **Resistencias** | 3 | 10kΩ para divisor Vref y 1kΩ para filtro |
| **Capacitor 100nF** | 1 | Filtro paso bajo para estabilidad en A0 |
| **Pulsador** | 1 | Cambio de modo (Medición/Calibración) |

---

## 📷 Esquema de conexión del circuito

![Esquema de conexión](esquema_conexion.png)

*Figura 1: Diagrama de conexión entre Arduino, sensor de conductividad, pantalla y pulsador.*

---

## 📷 Desde los simuladores (estoy trabajando en eso💪🏼✨)

![Esquema de Tinkercad](esquema_tinkercad.png)

*Figura 2: Esquema de la simulación de Tinkercad.*

![El dispositivo en los simuladores](simuladores.png)

*Figura 3: El dispositivo en los simuladores.*

---

## ⚡ Acondicionamiento de Señal (LM358)

Se utiliza el **LM358** para tratar la señal antes de ser procesada por el Arduino.
En el diagrama "Reemplazo Real Electrodo", se muestra cómo el potenciómetro se sustituye 1:1 por electrodos reales ($K^+$ y REF), permitiendo que el proyecto escale a una aplicación real sin cambios en el código.

---

## 🧠 Funcionamiento del Sistema

### 📊  Modelo Matemático

El sistema procesa la lectura del ADC (0-1023) y la convierte en voltaje para luego aplicar un modelo lineal:

$$Potasio (K^+) = (2.0 \times Voltaje) - 0.5$$

* **Seguridad:** El código incluye un límite para que el valor de potasio nunca sea menor a cero.

### 🛠️ 2.2. Modos de Funcionamiento

El pulsador permite alternar entre dos estados visuales:

1.  **Modo Medición (`mode = 0`):** Muestra el nivel de potasio calculado en **mmol/L**.
2.  **Modo Calibración (`mode = 1`):** Muestra el valor **ADC crudo** y el **voltaje** exacto detectado en A0, permitiendo ajustes técnicos precisos.

---

## 💻 Código Arduino Destacado

El software utiliza la librería `LiquidCrystal` y gestiona el cambio de modo mediante interrupción lógica por software:

```cpp

// Cambio de modo con botón (Antirrebote simple)
if (lastButtonState == HIGH && buttonState == LOW) {
  mode = !mode; // Alternar entre 0 y 1
  lcd.clear();
  delay(300);
}

// Modelo Matemático SIMULADO
potassium = (2.0 * voltage) - 0.5;

// Visualización condicional
if (mode == 0) {
  mostrarPotasio(potassium);
} else {
  mostrarCalibracion(raw, voltage);
}
```

---

## 🧠 Funcionamiento del código 

💻 1. Librerías y creación del objeto LCD

```cpp
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 9, 8, 10, 11, 12);
```

Se utiliza la librería estándar para manejar el LCD. A diferencia de versiones I2C, aquí se definen los pines digitales directamente: RS, Enable y el bus de datos de 4 bits (D4-D7).

---

👾 2. Variables de Estado 

```cpp
bool mode = 0; // 0 = Medición, 1 = Calibración
float voltage = 0.0;
float potassium = 0.0;
```

El código utiliza una variable booleana mode para alternar lo que el usuario ve en pantalla, permitiendo una herramienta versátil tanto para el paciente como para el técnico.

---

⏱️ 3. setup() y Bienvenida

```cpp
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  lcd.begin(16, 2);
  lcd.print("Medidor K+");
  lcd.setCursor(0, 1);
  lcd.print("Proyecto Hugo");
  delay(2000);
}
```
Inicializa el LCD y el botón. Muestra un mensaje inicial en memoria de Hugo para confirmar el arranque del sistema.

---

🔁 4. loop() – El Núcleo
Lectura del Botón: Detecta el flanco de bajada (cuando presionas) para cambiar el valor de mode.
Procesamiento Analógico: Toma la muestra de A0, la escala a 5V y aplica la ecuación lineal de potasio.
Visualización Condicional:
Si mode == 0: Llama a mostrarPotasio(), enfocándose en el valor final en mmol/L.
Si mode == 1: Llama a mostrarCalibracion(), exponiendo el valor ADC y el voltaje para ajustes de precisión.

---

## 📚 Documentación (en progreso, estoy trabajando en eso)
Para más detalles sobre el diseño, verificación y funcionamiento del dispositivo, consulta los siguientes archivos:

* [Doc - Descripción del dispositivo](Doc%20-%20Descripci%C3%B3n%20del%20dispositivo%20.pdf)
* [Doc - Ficha Técnica de mi dispositivo](Doc%20-%20Ficha%20T%C3%A9cnica%20de%20mi%20dispositivo%20.pdf)
* [Doc - Verificación en los simuladores](Doc%20-%20Verificaci%C3%B3n%20en%20los%20simuladores.pdf)

---

## 💖 Por qué medir Potasio?
Este proyecto siempre fue mucho más que electrónica.
Nunca fue solo medir valores, mostrar números o programar un microcontrolador.
Desde el primer día, fue una forma de cuidar.
Cuando pensé este dispositivo, lo hice desde el amor y desde el miedo. Desde ese impulso profundo que aparece cuando alguien que amás podría estar en riesgo, y vos no querés quedarte de brazos cruzados. El potasio, como electrolito esencial, apareció en este camino de la misma manera que apareció todo lo demás: como una preocupación real, concreta, humana.
Hugo, tenía problemas renales y dificultades para regular su potasio. Y cuando alguien tiene un riñón solo riñón y que no funciona como debería, el potasio deja de ser una palabra técnica y volverse algo vital, serio, delicado, incluso peligroso. Un valor alto o bajo puede significar arritmias, debilidad, complicaciones graves. Puede significar una urgencia. Puede significar miedo.
Y yo tenía miedo.
Miedo de que algo le pasara a Hugo quien Agus tamto amaba.
Miedo de no poder hacer nada.
Miedo de perder.
Medir potasio, entonces, no nació de un paper ni de una tabla clínica. Nació del deseo profundo de anticiparse al daño, de prevenir, de acompañar. De cuidar antes de que sea tarde. De ofrecer una herramienta, por más pequeña que fuera, que ayudara a entender el cuerpo y sus señales.
Este medidor de potasio es una extensión natural de ese mismo amor que dio origen al proyecto original. Es el mismo corazón, pero con más experiencia. Es la misma intención, pero con más conocimiento. Es la evolución de una idea que siempre quiso lo mismo: proteger.
Porque no todas las personas tienen acceso fácil a controles constantes.
Porque no todas las familias pueden pagar estudios frecuentes.
Porque no todos los cuerpos son escuchados a tiempo.
Este dispositivo intenta, humildemente, democratizar el monitoreo de un parámetro vital. No reemplaza a un médico, no pretende ser infalible. Pero acompaña. Advierte. Da información. Y a veces, eso ya es muchísimo.
Medir potasio, en este contexto, es un acto de amor técnico.
Es decir: me importa tu salud.
Es decir: quiero ayudarte a vivir mejor.
Es decir: tu cuerpo vale.
Este proyecto nació del amor por una persona, pero creció para abrazar a muchas.
Y aunque su origen sea íntimo, su propósito es colectivo.
Porque a veces cuidar también es crearr.
Y a veces medir también es amar.

---

Y también, a continuación te explico por qué mi medidor de salinidad básico con Arduino marca una diferencia real y tiene tanto valor:

🌍 1. Democratiza la medición de potasio

Mi dispositivo usa componentes accesibles y económicos, permitiendo que cualquier persona, bioquímico, paciente renal, deportista, estudiante o hasta un docente de escuela técnica, etc. pueda medir el potasio de una muestra.



---

🧪 2. Base para investigación científica en campo

Es una herramienta práctica para iniciar proyectos de investigación en biología, química o medicina, incluso en zonas con pocos recursos.

Puede usarse para monitoreo de salud (sudor/orina), donde medir como em el caso de Hugo, es clave.



---

🧰 3. Diseño modular, ampliable y profesional

El código y estructura están preparados para futuras ampliaciones:

Mostrar medición de potasio real cuando se disponga de la fórmula profesional.

Alertas leds.




---

🔍 4. Prototipo que respeta la lógica científica

Mide, calcula y muestra resultados de forma precisa y coherente.

No intenta inventar números ni sobreinterpretar: está preparado para que un profesional realice la calibración y se sume al sistema con su conocimiento.



---

💡 5. Pone la tecnología al servicio del conocimiento

En vez de limitarse a jugar con electrónica, mi proyecto está pensado para resolver problemas reales, como:


Monitoreo de salud (sudor/orina).

Evaluación del potasio.

Detectar cambios en muestras biológicas.




---

❤️ 6. Porque fue hecho con dedicación, aprendizaje y visión

Mi proyecto es auténtico: enfrentó límites, se adaptó, se documentó con claridad, y se preparó para el futuro.

Es un ejemplo de lo que puede lograrse con pensamiento crítico, sin necesidad de recursos infinitos ni laboratorios de élite.

Avanti todos los profesionales de la informática que tenemos ganas de ayudar.💖



---


## ❤️ Agradecimientos

Creo que ningún logro es verdaderamente individual. Todo lo que soy, lo que hago y lo que estoy logrando, es una construcción de muchas cosas que dejan en mi corazón, muchos abrazos, muchas palabras que me sostuvieron (y sostienen) cuando lo mecesito. Este proyecto, aunque nace de mí, también les pertenece a todos ustedes.

A mis padres, gracias por enseñarme el valor de ayudar, aún cuando no me tocaba, cuando no me toca, aún cuando el mundo mira para otro lado. Por ese ejemplo amoroso y firme que me dieron toda la vida: el de hacer hacer lo correcto, el de hacer las cosas con amor, con honestidad y con compromiso. Ustedes me mostraron lo que es tener un gran corazón, y si hoy estoy acá, es porque ese corazón me late desde ustedes y ese corazón, me lo dieron ustedes.

A mis hermanas, con las que tengo mil desacuerdos, diferencias, discusiones y formas opuestas de ver la vida… pero que, en el fondo, sé que me quieren con el alma. Gracias por ese orgullo que sienten por mí, aunque no siempre lo digan. Yo también las quiero y agradezco ser su hermanita.

A mis cuñados, que probablemente no entiendan ni la mitad de lo que estoy haciendo (y está bien jaja) pero que lo celebran igual, que se alegran conmigo y me hacen sentir que vale la pena. Gracias por ese amor!

A mis sobrinos, mis mellis bebés, mis rayitos de sol. Ustedes que no saben de discapacidad. Ustedes ven a su tía piola, la que les cumple los caprichos, la que les da su tiempo y amor. Gracias por quererme así, por hacerme sentir todo lo lindo que me hacen sentir, por mirarme con esos ojos que no discriminan ni burlan. Gracias peques, en serio.

A Marisol & Marcela, también les agradezco. Porque si hay algo que me salva cada día, son los gestos que no se compran: los abrazos que se dan con solo estar, las palabras que calman en medio de un caos, el cariño constante que ustedes me regalan solo porque me aman.
A veces la vida da ciertas cosas en los lugares que no esperábamos, las conocí de causalidad, y las encontré a ustedes. No son mis mamás biológicas, pero muchas veces me cuidan, me entienden y me abrigan el alma como solo una mamá lo haría. Y
eso vale oro.
Un rincón de paz en mi tormenta. Con ternura. Siempre supieron cuándo hablar, cuándo callar, cuándo solo estar. Son soles en mis días nublados, con ese amor que sostiene y abraza. Tengo esa confianza de hogar. Son empuje, risa y mis incondicionales. Con ustedes siento que puedo ser yo sin esconderme, reírme con nuestras anécdotas, nuestras locuras y ocurrencias, también ser yo sin suavizar lo que duele ni disimular lo que arde. No saben cuánto valoro eso, aunque no se los diga. Me dan lugar, me dan nombre, y me hacen sentir cuidada. Son ese tipo de amor que no necesita títulos porque se demuestra en lo cotidiano, en cada gesto, en cada "yo estoy".
Gracias por estar, por quererme como soy, por no rendirse cuando ni yo sabía cómo seguir. Gracias por enseñarme, sin decirlo, que el amor real es el que elige, el que acompaña.
Las amo con el alma entera. Y si alguna vez se preguntan qué significan para mí, espero que siempre lo sepan: son mi calma, mi ternura, mi fuerza... mis mamás elegidas, las mamás que me eligieron.
Con todo el amor que tengo, gracias💕

A mis amigas, Fi, Luji, Rosita, María, Esme, Luli, Luisi & Juli: las de siempre, las que no se van. Gracias por escucharme, por bancarme, por emocionarse conmigo, por reír, por llorar conmigo, por estar, por todo y por celebrar cada paso que doy. Gracias por amar mi corazón, mi personalidad, mi alegría y también quedarse cuando me caigo, estar para levantarme. Son hogar chicas💖.

A mis dos Fernandas, tan distintas, tan iguales en la forma hermosa en que me quieren. Gracias por ser espejo de todo lo que sí soy, por recordarme que valgo, que brillo, que ayudo, que importo. Gracias por su cariño incondicional, por su apoyo constante y por estar ahí siempre, atentas a cada logro, a cada lágrima, a cada sueño, las amo.

A mis profesores, especialmente a Celso, Laura & Claudita, verdaderos educadorares, formadores de mi alma y lo que soy no solo como profesional, también como persona. Gracias por despertar en mí la pasión por aprender, por enseñarme que el conocimiento es poder pero también es sensibilidad, es humanidad, es ayudar al otro, es lo que hacemos, es aportar, es ser buena gente. Por haberme siempre apoyado, por haber creído en mí antes que yo misma, por empujarme con amor a soñar en grande, a siempre más y más. Parte de lo que soy, parte de este proyecto, se los debo✨.

Y a la gente de a pie, a todos los que, al enterarse de este proyecto, se pusieron felices por mí aunque no supieran tanto, aunque no supieran los detalles. Gracias por esa buena onda sincera que me impulsó a seguir. Gracias por emocionarse, por darme palabras de apoyo, por todo ese power.

Este proyecto no lleva solo mi nombre. Lleva los abrazos, los gestos, los apoyos, los consejos, los mates, las lágrimas compartidas, las risas, las ganas de verme bien y logrando todo.
Este logro es de todos.
Gracias totales gente, de todo corazón.

 .-Poli💖

---

## 🙌 Créditos

Quiero expresar mi profundo agradecimiento a todas las personas que acompañaron este proyecto con su tiempo, apoyo y confianza.

**👨‍🏫 Profe Sergio Daniel Conde**

Este proyecto no estaría completo sin reconocer y agradecer profundamente al  
**Profesor Dr. Sergio Daniel Conde**.  

El profe Sergio Conde es, sin exagerar, uno de los mejores docentes que un estudiante puede tener.  
No solo por su inmenso recorrido académico (con múltiples distinciones, reconocimientos y premios que lo destacan a nivel nacional e internacional como referente en su área), sino porque combina esa brillantez con algo aún más valioso: **su calidad humana**.  

Es un profesor que **cree en sus alumnos**, que les dedica tiempo real, que acompaña, escucha y da visibilidad a sus ideas. Tiene esa rara capacidad de hacer sentir que cada uno importa, que cada proyecto, incluso los más pequeños, valen la pena. Logra lo que pocos: unir lo académico con lo humano, la ciencia con el corazón.  

En su carrera ha recibido numerosos **premios y menciones** por su labor, tanto en investigación como en docencia, pero quienes tuvimos la suerte de estar en sus clases sabemos que su mayor premio es la huella que deja en cada estudiante.  
Es un **genio en lo profesional**, pero también alguien profundamente **amoroso, cercano y generoso**.  

Por todo esto, quiero agradecerte de corazón, profe, por el apoyo, por darle visibilidad a este proyecto, por creer en mí incluso en los momentos en que yo misma dudaba. Gracias por demostrar con tu ejemplo que la enseñanza no es solo transmitir conocimiento, sino también inspirar, motivar y tender la mano.  

Este proyecto también lleva tu huella, porque detrás de cada idea que se concreta hay un eco de tu empuje, tu confianza y tu fe en que los estudiantes podemos lograr grandes cosas.  

**Con admiración, gratitud y cariño inmenso: gracias, profe.**

**💙 Luji**

Quiero agradecer especialmente a mi amiga **Luji** por el enorme apoyo psicológico que me ha dado a lo largo del desarrollo de este proyecto.

Su acompañamiento emocional fue clave para sostener el proceso de desarrollo, ella me ha aportado mucho para todo lo creativo, me ha ayudado a atravesar momentos difíciles y mantener la claridad mental necesaria para avanzar. Además, aportó una mirada externa valiosa orientada a la **prolijidad, el orden y el cuidado general del proyecto**.

Este tipo de apoyo, aunque no siempre visible en el código o el hardware, es fundamental para que un proyecto pueda nacer, crecer y sostenerse en el tiempo, amigas así son fundamentales.

---

##  📄 Licencia

Este proyecto fue desarrollado por Paulina Juich y registrado en la DNDA (Argentina) bajo el número de expediente EX-2025-78014687- el 18 de Julio de 2025.

Todo el contenido de este repositorio (código fuente, diseño electrónico, documentación) se encuentra protegido por derechos de autor.

⚠️ El incumplimiento de estas condiciones podrá derivar en acciones legales conforme a la Ley 11.723 de Propiedad Intelectual.

© 2025 Paulina Juich. Todos los derechos reservados.

- Uso personal, académico o educativo sin fines de lucro permitido con atribución.  
- Uso comercial o distribución requiere licencia o autorización expresa.  

Contacto para licencias: [paulinajuich4@gmail.com](mailto:paulinajuich4@gmail.com)

---

## ✍️ Autora

Paulina Juich

Técnica Analista Universitaria en Sistemas, Tech Support IT, Programadora de PC de la UTN, autora y desarrolladora de este dispositivo, su diseño técnico, lógico y funcional. 
 
Septiembre 2025 - 2026

---

### 🙌 Nota final

Este proyecto es un prototipo funcional con base sólida, creado con esfuerzo, amor, pasión y cuidado, que espera convertirse en una herramienta útil en monitoreo de líquidos biológicos, aplicaciones en química, biología, monitoreo ambiental y salud.

> 💓Este dispositivo no solo mide, también ama y cuida. Gracias por acompañarme.💓
> 
---
