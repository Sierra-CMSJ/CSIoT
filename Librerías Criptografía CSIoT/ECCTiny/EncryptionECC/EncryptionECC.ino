#include <tinyECC.h>

tinyECC ecc;

void setup() {
  Serial.begin(115200);
  //while (!Serial);

  ecc.plaintext = "alRT76q2oPqRsw";
  Serial.println("Texto Plano: " + ecc.plaintext);

  // Cifrar
  ecc.encrypt();

  /*
  // Exportar el cifrado como string
  Serial.println("Texto Cifrado (para copiar): ");
  Serial.println(ecc.ciphertext);
  */
}

void loop() {
  // Nada
}
