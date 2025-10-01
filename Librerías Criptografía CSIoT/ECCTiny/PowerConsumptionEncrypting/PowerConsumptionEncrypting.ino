#include <tinyECC.h>

const unsigned long interval_us = 3000;   // Intervalo en microsegundo

tinyECC ecc;

void setup() {
  Serial.begin(115200);
  //while (!Serial);

  ecc.plaintext = "alRT76q2oPqRsw";
  Serial.println("Texto Plano: " + ecc.plaintext);

}

void loop() {
  ecc.plaintext = "alRT76q2oPqRsw";
  ecc.encrypt();

  // Espera fija de en µs
  delayMicroseconds(interval_us);

}
