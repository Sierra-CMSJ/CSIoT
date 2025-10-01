#include <Arduino.h>
#include "RSA.h"

RSA::RSA() {}

// Función para verificar si un número es primo
bool RSA::is_prime(unsigned long n) {
  if (n <= 1) return false;
  if (n <= 3) return true;
  if (n % 2 == 0 || n % 3 == 0) return false;
  unsigned long i = 5;
  while (i * i <= n) {
    if (n % i == 0 || n % (i + 2) == 0) return false;
    i += 6;
  }
  return true;
}

// Función para calcular el máximo común divisor (GCD)
unsigned long RSA::gcd(unsigned long a, unsigned long b) {
  while (b != 0) {
    unsigned long temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

// 🔹 Nueva función para encontrar e (1 < e < phi_n y coprimo con phi_n)
unsigned long RSA::findE(unsigned long phi_n) {
  for (unsigned long e = 2; e < phi_n; e++) {
    if (gcd(e, phi_n) == 1) {
      return e;  // Retorna el primer valor válido
    }
  }
  return 0; // Caso excepcional
}

// Función para calcular el inverso modular usando el algoritmo extendido de Euclides
unsigned long RSA::mod_inverse(unsigned long e, unsigned long phi) {
  long x = 0, last_x = 1;
  long y = 1, last_y = 0;
  unsigned long original_phi = phi;

  while (phi != 0) {
    unsigned long q = e / phi;
    unsigned long temp = phi;
    phi = e % phi;
    e = temp;

    long temp_x = x;
    x = last_x - q * x;
    last_x = temp_x;

    long temp_y = y;
    y = last_y - q * y;
    last_y = temp_y;
  }

  if (last_x < 0) {
    last_x += original_phi;
  }
  return (unsigned long)last_x;
}

// Función para exponenciación modular (base^exp % mod)
unsigned long RSA::mod_exp(unsigned long long base, unsigned long exp, unsigned long mod) {
  unsigned long long result = 1;
  base = base % mod;
  while (exp > 0) {
    if (exp % 2 == 1) {
      result = (result * base) % mod;
    }
    exp = exp >> 1;
    base = (base * base) % mod;
  }
  return result;
}

// Función para generar claves públicas y privadas RSA
void RSA::generate_keys(unsigned long p, unsigned long q, unsigned long &e, unsigned long &d, unsigned long &n) {
  if (!is_prime(p) || !is_prime(q)) {
    Serial.println("Error: Ambos números deben ser primos.");
    return;
  }
  if (p == q) {
    Serial.println("Error: Los números primos p y q deben ser distintos.");
    return;
  }

  // Calcular n y phi_n
  n = p * q;
  unsigned long phi_n = ((p - 1)/gcd(p-1,q-1)) * (q - 1);

  e = findE(phi_n);
  d = mod_inverse(e, phi_n);

}

// Función para cifrar un mensaje usando la clave pública
void RSA::encrypt_message(const char* plain_text, unsigned long e, unsigned long n, unsigned long long encrypted_message[], int length) {
  for (int i = 0; i < length; i++) {
    encrypted_message[i] = mod_exp((unsigned long)plain_text[i], e, n);
    /*
    unsigned long long ascii_value = ((unsigned long)plain_text[i]);
    unsigned long long encrypted_char = 1;                   // Resultado inicial para exponenciación modular
    unsigned long long base = ascii_value;                   // Base de la operación (valor ASCII)

    // Exponenciación modular: base^e % n
    for (long j = 0; j < e; j++) {
      encrypted_char = (encrypted_char * base) % n;
    }
    encrypted_message[i] = encrypted_char;
    */
  }
}

// Función para descifrar un mensaje usando la clave privada
void RSA::decrypt_message(unsigned long long encrypted_message[], int length, unsigned long d, unsigned long n, char decrypted_message[]) {
  for (int i = 0; i < length; i++) {
    decrypted_message[i] = (char)mod_exp(encrypted_message[i], d, n);
  }
  decrypted_message[length] = '\0'; // Terminar la cadena
}
