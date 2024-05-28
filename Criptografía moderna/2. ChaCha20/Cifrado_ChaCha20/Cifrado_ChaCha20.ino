#include <Crypto.h>
#include <ChaCha.h>
#if defined(ESP8266) || defined(ESP32)
    #include <esp_system.h>
#endif

// Define la instancia de ChaCha
ChaCha chacha;

// Clave y vector de inicialización
byte key256[32];
byte iv[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// Texto plano aleatorio
const char *plainText = "APVCMSJ2024IOTTG";


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
    generateRandomKey(key256, sizeof(key256));
    }
    elapsed = micros() - start;
    Serial.print(elapsed / 500.0); // Tiempo promedio que tarda en generar la clave
    Serial.print("us por clave generada, ");
    Serial.print((500.0 * 1000000.0) / elapsed);
    Serial.println(" claves generadas por segundo");

    // Imprime la clave
    Serial.print("Clave: ");
    for (int i = 0; i < 32; i++) {
      Serial.print(key256[i], HEX);
      Serial.print(" ");
    }
    Serial.println();

    // Tamaño del texto
    size_t size = strlen(plainText);

    // Buffer para el texto encriptado
    byte* ciphertext = new byte[size];

    start=micros();
    for(int count=0; count < 500; ++count){
    // Establece la clave y el vector de inicialización
    chacha.setKey(key256, 32);
    chacha.setIV(iv, chacha.ivSize());
    // Encripta el texto
    chacha.encrypt(ciphertext, (const byte *)plainText, size);
    }
    elapsed = micros() - start;
    Serial.print(elapsed / (size * 500.0)); // Tiempo promedio que tarda en cifrar 
    Serial.print("us por byte cifrado, ");
    Serial.print((size * 500.0 * 1000000.0) / elapsed);
    Serial.println(" bytes cifrados por segundo");
    
    // Imprime el texto encriptado en formato hexadecimal
    Serial.print("Texto encriptado: ");
    for (int i = 0; i < size; i++) {
        Serial.print(ciphertext[i], HEX);
        Serial.print(" ");
    }
    Serial.println();
}

void loop() {

}