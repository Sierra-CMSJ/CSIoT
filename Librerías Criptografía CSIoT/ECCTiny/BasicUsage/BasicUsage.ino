#include <tinyECC.h>

tinyECC ecc;

void setup() {
  Serial.begin(115200);
  //while (!Serial);

  // Texto de entrada
  ecc.plaintext = "alRT76q2oPqRsw";
  // Tamaño del texto plano
  size_t plainTextSize = ecc.plaintext.length();
  Serial.println("Texto Plano: " + ecc.plaintext);
  Serial.print("Tamaño del texto plano: ");
  Serial.println(plainTextSize);

  // --- Cifrado ---
  ecc.encrypt();
  String cipher = ecc.ciphertext;
  Serial.println("Cipher Text: "+ecc.ciphertext);

  // --- Descifrado ---
  ecc.plaintext = F("");
  ecc.decrypt();
  ecc.ciphertext = F("");
  Serial.println("Decoded: "+ecc.plaintext);

}

void loop() {
  // No se repite nada
}
