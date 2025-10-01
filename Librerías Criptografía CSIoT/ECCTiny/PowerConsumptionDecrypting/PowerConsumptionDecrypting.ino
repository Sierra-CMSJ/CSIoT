#include <tinyECC.h>

const unsigned long interval_us = 3000;   // Intervalo en microsegundos

tinyECC ecc;

void setup() {
  Serial.begin(115200);
  //while (!Serial);

  // Aquí pegas el resultado del archivo anterior
  ecc.ciphertext = "106,285,814,527,14,166,371,628,775,553,453,618,263,379,135,929,142,911,307,174,236,892,309,961,418,440,599,119,418,440,582,633,558,334,810,550,707,971,649,103,1,5,771,958,14,166,403,855,27,367,954,834,142,911,801,226,14,166,942,493";

}

void loop() {
  ecc.decrypt();
  // Espera fija de en µs
  delayMicroseconds(interval_us);
}
