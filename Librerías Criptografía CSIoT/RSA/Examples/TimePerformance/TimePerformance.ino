#include <Arduino.h>
#include "RSA.h"

//Clave publica (e,n)
//Clave privada (d,n)
unsigned long e = 11;
unsigned long d = 568659191;
unsigned long n = 2502200483;

// Mensaje a cifrar
//const char* message = "A7kP9xL2mQ4zR8vB";

//const char* message = "A7kP9xL2mQ4zR8vBA7kP9xL2mQ4zR8vBA7kP9xL2mQ4zR8vBA7kP9xL2mQ4zR8vB";

const char* message = "A7kP9xL2mQ4zR8vBA7kP9xL2mQ4zR8vBA7kP9xL2mQ4zR8vBA7kP9xL2mQ4zR8vBA7kP9xL2mQ4zR8vBA7kP9xL2mQ4zR8vBA7kP9xL2mQ4zR8vBA7kP9xL2mQ4zR8vB";

const int plainTextSize = strlen(message);

RSA rsa;


// Función principal de Arduino
void setup() {
  Serial.begin(115200);
  while (!Serial);

  unsigned long totalEncryptTime = 0;
  unsigned long totalDecryptTime = 0;

  unsigned long long encrypted_message[plainTextSize];
  char decrypted_message[plainTextSize + 1];

  for (int i = 0; i < 10; i++) {
    // Medir tiempo de encriptación
    unsigned long startEnc = micros();
    rsa.encrypt_message(message, e, n, encrypted_message, plainTextSize);
    unsigned long endEnc = micros();
    totalEncryptTime += (endEnc - startEnc);

    // Medir tiempo de desencriptación
    unsigned long startDec = micros();
    rsa.decrypt_message(encrypted_message, plainTextSize, d, n, decrypted_message);
    unsigned long endDec = micros();
    totalDecryptTime += (endDec - startDec);
  }

  // Cálculo de promedios
  float avgEncrypt = totalEncryptTime / 10.0;
  float avgDecrypt = totalDecryptTime / 10.0;

  // Mostramos resultados
  Serial.println("=== RESULTADOS PROMEDIO (100 iteraciones) ===");
  Serial.print("Tiempo promedio de cifrado (us): ");
  Serial.println(avgEncrypt);
  Serial.print("Tiempo promedio de descifrado (us): ");
  Serial.println(avgDecrypt);

  // Mostramos resultados
  Serial.println("=== RESULTADOS PROMEDIO (100 iteraciones [Byte/us]) ===");
  Serial.print("Tiempo promedio de cifrado (Byte/us): ");
  Serial.println(avgEncrypt/plainTextSize);
  Serial.print("Tiempo promedio de descifrado (Byte/us): ");
  Serial.println(avgDecrypt/plainTextSize);

}

void loop() {
}