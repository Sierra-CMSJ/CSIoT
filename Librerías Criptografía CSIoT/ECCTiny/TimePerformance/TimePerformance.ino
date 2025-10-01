#include <tinyECC.h>

tinyECC ecc;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  unsigned long totalEncryptTime = 0;
  unsigned long totalDecryptTime = 0;

  // Texto de entrada
  ecc.plaintext = "alRT76q2oPqRsw";
  Serial.println("Texto Plano: " + ecc.plaintext);

  // Tamaño del texto plano
  size_t plainTextSize = ecc.plaintext.length();

  // Número de iteraciones
  const int ITERACIONES = 5;

  for (int i = 0; i < ITERACIONES; i++) {
    ecc.plaintext = "alRT76q2oPqRsw";
    // Medir tiempo de encriptación
    unsigned long startEnc = micros();
    ecc.encrypt();
    unsigned long endEnc = micros();
    totalEncryptTime += (endEnc - startEnc);

    // Medir tiempo de desencriptación
    unsigned long startDec = micros();
    ecc.decrypt();
    unsigned long endDec = micros();
    totalDecryptTime += (endDec - startDec);
  }

  // Cálculo de promedios
  float avgEncrypt = totalEncryptTime / (float)ITERACIONES;
  float avgDecrypt = totalDecryptTime / (float)ITERACIONES;

  // Mostramos resultados
  Serial.println("=== RESULTADOS PROMEDIO ===");
  Serial.print("Iteraciones: ");
  Serial.println(ITERACIONES);

  Serial.print("Tiempo promedio de cifrado (us): ");
  Serial.println(avgEncrypt);
  Serial.print("Tiempo promedio de descifrado (us): ");
  Serial.println(avgDecrypt);

  Serial.println("=== RESULTADOS NORMALIZADOS (Byte/us) ===");
  Serial.print("Cifrado (Byte/us): ");
  Serial.println(avgEncrypt / plainTextSize);
  Serial.print("Descifrado (Byte/us): ");
  Serial.println(avgDecrypt / plainTextSize);

  String cipher = ecc.ciphertext;

  // Imprimir texto cifrado (en HEX para visualizar mejor los bytes)
  Serial.print("Texto Cifrado (HEX): ");
  for (size_t i = 0; i < cipher.length(); i++) {
    if (cipher[i] < 16) Serial.print("0");  
    Serial.print(cipher[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  String decrypted = ecc.plaintext;

  Serial.println("Texto Descifrado: " + decrypted);

}

void loop() {
  // No se repite nada
}
