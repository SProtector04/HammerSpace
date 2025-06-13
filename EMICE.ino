#include <ESP32Servo.h>

// --- Objetos Servo ---
Servo servoPan;
Servo servoTilt;
const int pinPan  = 17;
const int pinTilt = 16;

// --- Pines LDR ---
const int LDR1 = 33;
const int LDR2 = 32;
const int LDR3 = 35;
const int LDR4 = 34;

// --- Variables de lectura ---
int ldr1_val, ldr2_val, ldr3_val, ldr4_val;
int ldr1_norm, ldr2_norm, ldr3_norm, ldr4_norm;

void setup() {
  Serial.begin(115200);
  while(!Serial) { delay(10); }  // Espera el monitor Serial

  // Inicializa servos en posición central
  servoPan.attach(pinPan);
  servoTilt.attach(pinTilt);
  servoPan.write(90);
  servoTilt.write(90);

  // Configura pines LDR como entrada
  pinMode(LDR1, INPUT);
  pinMode(LDR2, INPUT);
  pinMode(LDR3, INPUT);
  pinMode(LDR4, INPUT);

  Serial.println("Listo: leyendo LDR y moviendo servos.");
}

void loop() {
  lecturaLDR();
  normalizarSensores();
  movimientoEjes();
  imprimirEstado();
  delay(100);
}

void lecturaLDR() {
  ldr1_val = analogRead(LDR1);
  if (ldr1_val <= 200) ldr1_val = 200;
  ldr1_val = map(ldr1_val, 200, 4095, 0, 4095);
  ldr2_val = analogRead(LDR2);
  ldr3_val = analogRead(LDR3);
  ldr4_val = analogRead(LDR4);

}

void normalizarSensores() {
  const int umbral = 3500; // 

  ldr1_norm = (ldr1_val > umbral) ? 1 : 0;
  ldr2_norm = (ldr2_val > umbral) ? 1 : 0;
  ldr3_norm = (ldr3_val > umbral) ? 1 : 0;
  ldr4_norm = (ldr4_val > umbral) ? 1 : 0;
}

void movimientoEjes() {
  // Fórmulas de ejemplo (ajusta según tu montaje)
  int angTilt   = 45   * (3*ldr1_norm + ldr2_norm + 3*ldr3_norm + ldr4_norm - 4 * (ldr1_norm * ldr2_norm) - 2 * (ldr1_norm * ldr4_norm) - 2 * (ldr2_norm * ldr3_norm) - 4 * (ldr3_norm * ldr4_norm));
  int angPan = 15 * (11*ldr1_norm + 1*ldr2_norm + 1*ldr3_norm + 11*ldr4_norm - (11 * (ldr1_norm * ldr2_norm)) - (11 * (ldr1_norm * ldr4_norm)) - (1 * (ldr3_norm * ldr2_norm)) - (1 * (ldr3_norm * ldr4_norm)) + (ldr1_norm * ldr2_norm * ldr3_norm * ldr4_norm) * 6);

  // Limita al rango servo 0–180°
  angPan  = constrain(angPan,  0, 180);
  angTilt = constrain(angTilt, 0, 180);

  servoPan.write( angPan );
  servoTilt.write( angTilt );
}


void imprimirEstado() {
  // servo.read() devuelve el último valor escrito
  int posPan  = servoPan.read();
  int posTilt = servoTilt.read();

  Serial.printf(
    "Norm: L1=%d L2=%d L3=%d L4=%d | "
    "Raw: %4d %4d %4d %4d | "
    "Pan=%3d° Tilt=%3d°\n",
    ldr1_norm, ldr2_norm, ldr3_norm, ldr4_norm,
    ldr1_val,  ldr2_val,  ldr3_val,  ldr4_val,
    posPan, posTilt
  );
}