#include <Arduino.h>
#include "RSA.h"

RSA rsa;

// Función principal de Arduino
void setup() {
  //while (!Serial);
  Serial.begin(115200);

  //Seleccion de dos numero primos inferiores a 60000
  unsigned long p = 50021;
  unsigned long q = 50023;
  unsigned long e, d, n;

  rsa.generate_keys(p, q, e, d, n);

  Serial.print("Clave publica: ");
  Serial.print(e);
  Serial.print("-");
  Serial.println(n);
  Serial.print("Clave privada: ");
  Serial.print(d);
  Serial.print("-");
  Serial.println(n);
}

void loop() {
}