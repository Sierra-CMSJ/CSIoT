#include <Arduino.h>
#include "RSA.h"

const unsigned long interval_us = 3000;   // Intervalo en microsegundo

//Clave publica (e,n)
//Clave privada (d,n)
unsigned long e = 11;
unsigned long d = 568659191;
unsigned long n = 2502200483;

// Mensaje a cifrar
//const char* message = "A7kP9xL2mQ4zR8vB";         //16

const char* message = "A7kP9xL2mQ4zR8vBA7kP9xL2mQ4zR8vBA7kP9xL2mQ4zR8vBA7kP9xL2mQ4zR8vB";         //64

//const char* message = "A7kP9xL2mQ4zR8vBA7kP9xL2mQ4zR8vBA7kP9xL2mQ4zR8vBA7kP9xL2mQ4zR8vBA7kP9xL2mQ4zR8vBA7kP9xL2mQ4zR8vBA7kP9xL2mQ4zR8vBA7kP9xL2mQ4zR8vB";         //128

const int plainTextSize = strlen(message);
unsigned long long encrypted_message[64];         //Cambiar el tamaño dependiendo del tamaño de texto plano

RSA rsa;

// Función principal de Arduino
void setup() {
  Serial.begin(115200);
  //while (!Serial);
}

void loop() {
  for (int i = 0; i < 10; i++) {
    rsa.encrypt_message(message, e, n, encrypted_message, plainTextSize);
  }

  /*
  Serial.println("\nMensaje cifrado:");
  for (int i = 0; i < plainTextSize; i++) {
    Serial.print((unsigned long)encrypted_message[i]);
    Serial.print(" ");
  }
  */

  // Espera fija de en µs
  delayMicroseconds(interval_us);
}