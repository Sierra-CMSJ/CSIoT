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
const char *plainText = "La criptografía";

// Función para imprimir un byte en formato hexadecimal
void printByteAsHex(byte b) {
    if (b < 0x10) {
        Serial.print("0"); // Agrega un cero inicial si el byte es menor que 0x10
    }
    Serial.print(b, HEX); // Imprime el byte en hexadecimal
}

// Función para imprimir un arreglo de bytes en formato hexadecimal
void printBytesAsHex(const byte *data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printByteAsHex(data[i]);
        if (i < size - 1) {
            Serial.print(" "); // Agrega un espacio entre los bytes
        }
    }
}

void printKeyAsHex(const byte *key, size_t size) {
    printBytesAsHex(key, size);
    Serial.println();
}

#if defined(ESP8266) || defined(ESP32)
    void generateRandomKey(byte *key, size_t size) {
        uint32_t seed = esp_random(); // Genera una semilla utilizando esp_random()
        randomSeed(seed); // Utiliza la semilla para la generación de números aleatorios
        for (size_t i = 0; i < size; ++i) {
            key[i] = random(256); // Genera un número aleatorio entre 0 y 255
        }
    }
#else
    void generateRandomKey(byte *key, size_t size) {
        randomSeed(analogRead(0)); // Semilla para la generación de números aleatorios
        for (size_t i = 0; i < size; ++i) {
            key[i] = random(256); // Genera un número aleatorio entre 0 y 255
        }
    }
#endif

// Función para encriptar un texto, imprimirlo y luego devolverlo
byte* encryptText(const byte *key, const byte *iv, const char *plaintext, size_t size) {
    // Establece la clave y el vector de inicialización
    chacha.setKey(key, 32);
    chacha.setIV(iv, chacha.ivSize());

    // Buffer para el texto encriptado
    byte* ciphertext = new byte[size];

    // Encripta el texto
    chacha.encrypt(ciphertext, (const byte *)plaintext, size);

    // Imprime el texto encriptado en formato hexadecimal
    Serial.print("Texto encriptado: \"");
    printBytesAsHex(ciphertext, size);
    Serial.println("\"");

    // Devuelve el texto encriptado
    return ciphertext;
}


void setup() {
    Serial.begin(115200);

    generateRandomKey(key256, sizeof(key256));

    // Tamaño del texto
    size_t size = strlen(plainText);


    Serial.print("Clave de 256 bits: ");
    printKeyAsHex(key256, sizeof(key256));
    Serial.println();

    // Encriptar el texto con la clave de 256 bits
    byte* cipherText256 = encryptText(key256, iv, plainText, size);
    Serial.println();

}

void loop() {

}
