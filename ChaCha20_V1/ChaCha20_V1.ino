#include <Crypto.h>
#include <ChaCha.h>
#if defined(ESP8266) || defined(ESP32)
    #include <esp_system.h>
#endif

// Define la instancia de ChaCha
ChaCha chacha;

// Clave y vector de inicialización
byte key128[16];
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
    Serial.print("Clave en formato hexadecimal: ");
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

// Función para desencriptar un texto
void decryptText(const byte *key, const byte *iv, const byte *ciphertext, size_t size) {
    // Establece la clave y el vector de inicialización
    chacha.setKey(key, 32);
    chacha.setIV(iv, chacha.ivSize());

    // Buffer para el texto desencriptado
    char* decryptedText = new char[size];

    // Desencripta el texto
    chacha.decrypt((byte *)decryptedText, ciphertext, size);

    // Imprime el texto desencriptado en formato de cadena de texto
    Serial.print("Texto desencriptado: \"");
    Serial.print(decryptedText);
    Serial.println("\"");
}

void setup() {
    Serial.begin(115200);

    unsigned long startKey128 = micros();
    generateRandomKey(key128, sizeof(key128));
    unsigned long endKey128 = micros();
    Serial.print("Tiempo de generación clave de 128 bits: ");
    Serial.print(endKey128 - startKey128);
    Serial.println(" microsegundos");
    Serial.println();

    unsigned long startKey256 = micros();
    generateRandomKey(key256, sizeof(key256));
    unsigned long endKey256 = micros();
    Serial.print("Tiempo de generación clave de 256 bits: ");
    Serial.print(endKey256 - startKey256);
    Serial.println(" microsegundos");
    Serial.println();


    // Tamaño del texto
    size_t size = strlen(plainText);

    // Imprimir las claves en formato hexadecimal
    Serial.println();
    Serial.print("Clave de 128 bits: ");
    printKeyAsHex(key128, sizeof(key128));
    Serial.println();

    Serial.print("Clave de 256 bits: ");
    printKeyAsHex(key256, sizeof(key256));
    Serial.println();

    // Encriptar el texto con la clave de 128 bits
    unsigned long startEncrypt128 = micros();
    byte* cipherText128 = encryptText(key128, iv, plainText, size);
    unsigned long endEncrypt128 = micros();
    Serial.print("Tiempo de encriptación con clave de 128 bits: ");
    Serial.print(endEncrypt128 - startEncrypt128);
    Serial.println(" microsegundos");
    Serial.println();

    // Desencriptar el texto con la clave de 128 bits
    unsigned long startDecrypt128 = micros();
    decryptText(key128, iv, cipherText128, size);
    unsigned long endDecrypt128 = micros();
    Serial.print("Tiempo de desencriptación con clave de 128 bits: ");
    Serial.print(endDecrypt128 - startDecrypt128);
    Serial.println(" microsegundos");
    Serial.println();

    // Encriptar el texto con la clave de 256 bits
    unsigned long startEncrypt256 = micros();
    byte* cipherText256 = encryptText(key256, iv, plainText, size);
    unsigned long endEncrypt256 = micros();
    Serial.print("Tiempo de encriptación con clave de 256 bits: ");
    Serial.print(endEncrypt256 - startEncrypt256);
    Serial.println(" microsegundos");
    Serial.println();

    // Desencriptar el texto con la clave de 256 bits
    unsigned long startDecrypt256 = micros();
    decryptText(key256, iv, cipherText256, size);
    unsigned long endDecrypt256 = micros();
    Serial.print("Tiempo de desencriptación con clave de 256 bits: ");
    Serial.print(endDecrypt256 - startDecrypt256);
    Serial.println(" microsegundos");
    Serial.println();

}

void loop() {

}
