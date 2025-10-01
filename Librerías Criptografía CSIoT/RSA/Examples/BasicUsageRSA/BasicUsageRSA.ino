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

  //Variables para guardar claves
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

  // Mensaje a cifrar
  const char* message = "A7kP9xL2mQ4zR8vB";
  int length = strlen(message);

  // Cifrar el mensaje
  unsigned long long encrypted_message[length];
  rsa.encrypt_message(message, e, n, encrypted_message, length);
  Serial.println("\nMensaje cifrado:");
  for (int i = 0; i < length; i++) {
    Serial.print((unsigned long)encrypted_message[i]);
    Serial.print(" ");
  }
  Serial.println();

  // Descifrar el mensaje
  char decrypted_message[length + 1];
  rsa.decrypt_message(encrypted_message, length, d, n, decrypted_message);
  Serial.println("\nMensaje descifrado:");
  Serial.println(decrypted_message);

}

void loop() {
}