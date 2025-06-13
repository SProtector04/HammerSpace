#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <DHT.h>
#include <ESP32Servo.h>

// Pines sensores
const int sensorHumedadPin = 13;  // Humedad del suelo (analógico)
const int sensorLluviaPin  = 12;  // Lluvia (digital)
const int sensorLuzPin     = 2;   // Luz (analógico)
const int DHTPIN           = 27;  // DHT11

// Pines servos y bomba de riego
const int servoXPin = 17; // Cambiado para que servoX (pan) esté en pin 17
const int servoYPin = 16; // Cambiado para que servoY (tilt) esté en pin 16
const int bombaRiegoPin = 25;

// Pines LDR
const int LDR1 = 35;
const int LDR2 = 32;
const int LDR3 = 33;
const int LDR4 = 34;

// Variables de lectura LDR
int ldr1_val, ldr2_val, ldr3_val, ldr4_val;
int ldr1_norm, ldr2_norm, ldr3_norm, ldr4_norm;

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP085 bmp; // BMP180 y BMP085 usan la misma librería

// Objetos Servo
Servo servoXMotor;
Servo servoYMotor;

// Variables para los valores recibidos por serial
int perfil = 0;
int automatico = 1; // Cambiado a int (0 o 1)
int servoX = 90;
int servoY = 90;
int riegoForzado = 0; // Cambiado a int (0 o 1)

void lecturaLDR() {
  ldr1_val = analogRead(LDR1);
  if (ldr1_val <= 200) ldr1_val = 200;
  ldr1_val = map(ldr1_val, 200, 3000, 0, 4095);
  ldr2_val = analogRead(LDR2);
  ldr3_val = analogRead(LDR3);
  ldr4_val = analogRead(LDR4);
}

void normalizarSensores() {
  const int umbral = 3000;
  ldr1_norm = (ldr1_val > umbral) ? 1 : 0;
  ldr2_norm = (ldr2_val > umbral) ? 1 : 0;
  ldr3_norm = (ldr3_val > umbral) ? 1 : 0;
  ldr4_norm = (ldr4_val > umbral) ? 1 : 0;
}

void movimientoEjes() {
  int activeLDRs = ldr1_norm + ldr2_norm + ldr3_norm + ldr4_norm;

  if (activeLDRs == 3) {
    if (ldr1_norm && ldr2_norm && ldr3_norm) {
      ldr1_norm = 0; ldr3_norm = 0;
    } else if (ldr2_norm && ldr3_norm && ldr4_norm) {
      ldr2_norm = 0; ldr4_norm = 0;
    } else if (ldr3_norm && ldr4_norm && ldr1_norm) {
      ldr3_norm = 0; ldr1_norm = 0;
    } else if (ldr4_norm && ldr1_norm && ldr2_norm) {
      ldr4_norm = 0; ldr2_norm = 0;
    }
  }

  int angPan = (ldr1_norm && ldr3_norm) || (ldr2_norm && ldr4_norm) ? 90 :
               constrain(15 * (11 * ldr1_norm + 1 * ldr2_norm + 1 * ldr3_norm + 11 * ldr4_norm
               - (11 * (ldr1_norm * ldr2_norm)) - (11 * (ldr1_norm * ldr4_norm))
               - (1 * (ldr3_norm * ldr2_norm)) - (1 * (ldr3_norm * ldr4_norm))
               + (ldr1_norm * ldr2_norm * ldr3_norm * ldr4_norm) * 6), 15, 165);

  int angTilt = (ldr1_norm && ldr3_norm) || (ldr2_norm && ldr4_norm) ? 0 :
                constrain(45 * (3 * ldr1_norm + ldr2_norm + 3 * ldr3_norm + ldr4_norm
                - 4 * (ldr1_norm * ldr2_norm) - 2 * (ldr1_norm * ldr4_norm)
                - 2 * (ldr2_norm * ldr3_norm) - 4 * (ldr3_norm * ldr4_norm)), 0, 180);

  servoXMotor.write(angPan);
  servoYMotor.write(angTilt);
}

void imprimirEstado() {
  // Serial.printf(
  //   "Norm: L1=%d L2=%d L3=%d L4=%d | "
  //   "Raw: %4d %4d %4d %4d | "
  //   "Pan=%3d° Tilt=%3d°\n",
  //   ldr1_norm, ldr2_norm, ldr3_norm, ldr4_norm,
  //   ldr1_val,  ldr2_val,  ldr3_val,  ldr4_val,
  //   servoXMotor.read(), servoYMotor.read()
  // );
}

void setup() {
  Serial.begin(115200);

  // Iniciar sensores
  dht.begin();
  if (!bmp.begin()) {
    Serial.println("No se detectó el sensor BMP180. Verifica la conexión.");
    while (1);
  }

  pinMode(sensorHumedadPin, INPUT);
  pinMode(sensorLluviaPin, INPUT);
  pinMode(sensorLuzPin, INPUT);

  // Configurar servos y bomba de riego
  servoXMotor.attach(servoXPin);
  servoYMotor.attach(servoYPin);
  pinMode(bombaRiegoPin, OUTPUT);
  digitalWrite(bombaRiegoPin, LOW); // Apagar bomba inicialmente

  // Configurar pines LDR como entrada
  pinMode(LDR1, INPUT);
  pinMode(LDR2, INPUT);
  pinMode(LDR3, INPUT);
  pinMode(LDR4, INPUT);

  Serial.println("Iniciando lectura de sensores...");
}

void recibir_serial() {
  if (Serial.available() > 0) {
    String linea = Serial.readStringUntil('\n'); // Leer línea hasta el salto de línea
    linea.trim(); // Eliminar espacios en blanco al inicio y final

    // Dividir la línea en valores separados por comas
    int indiceComa = 0;
    String valores[5];
    int contadorValores = 0;
    while (contadorValores < 5 && linea.length() > 0) {
      indiceComa = linea.indexOf(',');
      if (indiceComa == -1) {
        valores[contadorValores] = linea; // Último valor
        linea = "";
      } else {
        valores[contadorValores] = linea.substring(0, indiceComa);
        linea = linea.substring(indiceComa + 1);
      }
      contadorValores++;
    }

    // Validar que se recibieron exactamente 5 valores
    if (contadorValores == 5) {
      // Asignar los valores a las variables correspondientes
      perfil = valores[0].toInt();
      automatico = valores[1].toInt();
      servoX = valores[2].toInt();
      servoY = valores[3].toInt();
      riegoForzado = valores[4].toInt();

      // Validar y ajustar valores si es necesario
      servoX = constrain(servoX, 0, 180);
      servoY = constrain(servoY, 0, 180);
    } else {
      Serial.println("Error: Datos serial no válidos.");
    }
  }
}

void imprimirDatosSerial(String datos) {
  Serial.println("======= DATOS RECIBIDOS =======");
  Serial.println(datos);
  Serial.println("================================");
}

void loop() {
  int humedadSueloRaw = analogRead(sensorHumedadPin);
  int humedadSuelo = map(humedadSueloRaw, 4095, 0, 0, 100);
  humedadSuelo = constrain(humedadSuelo, 0, 100);

  int lluvia = digitalRead(sensorLluviaPin);
  int luzRaw = analogRead(sensorLuzPin);
  int nivelLuz = map(luzRaw, 2500, 40, 0, 100);
  nivelLuz = constrain(nivelLuz, 0, 100);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float presion = bmp.readPressure() / 100.0; // hPa

  // Serial.println("======= LECTURA SENSORES =======");
  // Serial.print("Humedad Suelo (%): "); Serial.println(humedadSuelo);
  // Serial.print("Lluvia detectada: "); Serial.println(lluvia ? "Sí" : "No");
  // Serial.print("Luz (%): "); Serial.println(nivelLuz);
  // Serial.print("Temperatura (°C): "); Serial.println(t);
  // Serial.print("Humedad (%): "); Serial.println(h);
  // Serial.print("Presión (hPa): "); Serial.println(presion);
  // Serial.println("================================");

  Serial.printf("%f,%d,%d,%d,%d\n", t, humedadSuelo, humedadSuelo, nivelLuz, 0); // probabilidad no implementado

  if (automatico == 1) { // Solo permitir control automático si automatico es 1
    lecturaLDR();
    normalizarSensores();
    movimientoEjes();
    // imprimirEstado(); // Comentado para evitar salida serial
  } else {
    // Control manual de servos
    servoXMotor.write(servoX);
    servoYMotor.write(servoY);

    // Control manual de la bomba de riego
    if (riegoForzado == 1) {
      digitalWrite(bombaRiegoPin, HIGH); // Encender bomba
    } else {
      digitalWrite(bombaRiegoPin, LOW); // Apagar bomba
    }
  }

  if (Serial.available() > 0) {
    String datosRecibidos = Serial.readStringUntil('\n'); // Leer datos hasta salto de línea
    datosRecibidos.trim(); // Eliminar espacios en blanco
    imprimirDatosSerial(datosRecibidos); // Imprimir datos recibidos
  }

  recibir_serial(); // Llamar a la función para recibir datos por serial

  delay(2000);
}