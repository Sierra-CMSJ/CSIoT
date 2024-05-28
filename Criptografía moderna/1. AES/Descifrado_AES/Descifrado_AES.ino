#include <AESLib.h>

AESLib aesLib;

// Clave de cifrado AES
byte aes_key[32] = { 0x6A, 0xBF, 0x2F, 0x4A, 0x41, 0xC5, 0xFF, 0x28, 0x32, 0x72, 0x51, 0x42, 0x3D, 0xE9, 0xF1, 0xD3, 0x44, 0x21, 0xCB,
 0x62, 0xD9, 0x8E, 0x88, 0x7F, 0x3C, 0x51, 0xE3, 0xFD, 0xC3, 0x4C, 0x70, 0x16 };

// Vector de inicialización IV
byte aes_iv[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00 };

// Texto cifrado en formato hexadecimal
const char* ciphertext_hex = "C611AB80A5D8DBF26F671759FD61630B";

// Función para convertir una cadena hexadecimal a un array de bytes
void hexStringToByteArray(const char* hexString, byte* byteArray, size_t length) {
  for (size_t i = 0; i < length; ++i) {
    unsigned int byte;
    sscanf(hexString + 2 * i, "%02x", &byte);
    byteArray[i] = byte;
  }
}

void setup() {
  Serial.begin(115200);
  while(!Serial){
  // Espera que el monitor serial se inicie
  }
  unsigned long start;
  unsigned long elapsed;

  // Convertir el texto cifrado a un array de bytes
  byte ciphertext[strlen(ciphertext_hex) / 2];
  hexStringToByteArray(ciphertext_hex, ciphertext, sizeof(ciphertext));

  // Tamaño del texto
  size_t size = strlen(ciphertext_hex);

  // Buffer para el texto descifrado
  char plaintext[sizeof(ciphertext) + 1];

   // Medición del tiempo de cifrado
  start=micros();
  for(int count=0; count < 500; ++count){
  // Reiniciar el IV a su valor original
  byte aes_iv_reset[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00 };
  memcpy(aes_iv, aes_iv_reset, sizeof(aes_iv));
  // Descifrar el texto
  aesLib.decrypt(ciphertext, sizeof(ciphertext), (byte*)plaintext, aes_key, sizeof(aes_key), aes_iv);
  }
  elapsed = micros() - start;
  Serial.print(elapsed / (size * 500.0)); // Tiempo promedio que tarda en cifrar 
  Serial.print("us por byte descifrado, ");
  Serial.print((size * 500.0 * 1000000.0) / elapsed);
  Serial.println(" bytes descifrados por segundo");
  
  // Asegurarse de que el texto descifrado sea una cadena válida
  plaintext[sizeof(ciphertext)] = '\0';

  // Imprimir el texto descifrado
  Serial.print("Texto descifrado: ");
  Serial.println(plaintext);
}

void loop() {
}
