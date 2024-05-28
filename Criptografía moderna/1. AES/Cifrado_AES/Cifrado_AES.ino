// AES modo cbc donde se cifra en bloques del tamaño que tenga el IV. Para completar tamaños en datos que no sean multiplos de la 
// Longitud del IV se añade padding osea rellenos a la informacion cifrada.
#include <AESLib.h>

AESLib aesLib;

// Texto plano
const char* plaintext = "APVCMSJ2024IOTTG";

// Clave de cifrado AES
byte aes_key[32];

// Vector de inicialización IV
byte aes_iv[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00 };

void generateRandomKey(byte *key, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        key[i] = random(256); // Genera un número aleatorio entre 0 y 255
    }
}

void setup() {
  Serial.begin(115200);
  unsigned long start;
  unsigned long elapsed;

  // Semilla para la generación de números aleatorios
  #if defined(ESP8266) || defined(ESP32)
      randomSeed(esp_random());
  #else
      randomSeed(analogRead(0));
  #endif

  // Medición del tiempo de generación de clave
  start=micros();
  for(int count=0; count < 500; ++count){
    // Genera la clave
    generateRandomKey(aes_key, sizeof(aes_key));
  }
  elapsed = micros() - start;
  Serial.print(elapsed / 500.0); // Tiempo promedio que tarda en generar la clave
  Serial.print("us por clave generada, ");
  Serial.print((500.0 * 1000000.0) / elapsed);
  Serial.println(" claves generadas por segundo");

  // Imprime la clave
  Serial.print("Clave: ");
  for (int i = 0; i < 32; i++) {
    Serial.print(aes_key[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  // Tamaño del texto
  size_t size = strlen(plaintext);

  // Asegurarse de que el tamaño del buffer de texto cifrado sea un múltiplo de 16
  size_t paddedSize = ((size + 15) / 16) * 16;

  // Buffer para el texto encriptado
  byte ciphertext[paddedSize];

  // Medición del tiempo de cifrado
  start=micros();
  for(int count=0; count < 500; ++count){
  // Reiniciar el IV a su valor original
  byte aes_iv_reset[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00 };
  memcpy(aes_iv, aes_iv_reset, sizeof(aes_iv));
  // Cifrar el texto
  aesLib.encrypt((const byte*)plaintext, strlen(plaintext), ciphertext, aes_key, sizeof(aes_key), aes_iv);
  }
  elapsed = micros() - start;
  Serial.print(elapsed / (size * 500.0)); // Tiempo promedio que tarda en cifrar 
  Serial.print("us por byte cifrado, ");
  Serial.print((size * 500.0 * 1000000.0) / elapsed);
  Serial.println(" bytes cifrados por segundo");

  // Imprimir el texto cifrado en formato hexadecimal
  Serial.print("Texto cifrado: ");
  for (int i = 0; i < paddedSize; i++) {
    if(ciphertext[i] < 16) Serial.print("0");
    Serial.print(ciphertext[i], HEX);
  }
}

void loop() {
}