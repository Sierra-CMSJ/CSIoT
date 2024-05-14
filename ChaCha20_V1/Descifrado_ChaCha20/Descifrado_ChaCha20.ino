
#include <Crypto.h>
#include <ChaCha.h>

// Define la instancia de ChaCha
ChaCha chacha;

// Clave y vector de inicialización
byte key256[32] = {0xFE, 0x04, 0xE5, 0x4B, 0x87, 0x21, 0x4F, 0x7C, 0x9B, 0x46, 0x7F, 0xF6, 0x19, 0x0D, 0xCA, 0x70,
0xB7, 0xB9, 0x4C, 0x56, 0x28, 0x44, 0xE2, 0x1F, 0x88, 0x03, 0xF5, 0x5F, 0x97, 0xAA, 0x71, 0xBA}; // Esta clave será la misma con la que se cifró la información
byte iv[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// Texto cifrado
byte cipherText[] = {0x3F, 0x13, 0x04, 0xB0, 0x31, 0xEF, 0xD2, 0xB8, 0xB1, 0x65, 0xCC, 0x52, 0x11, 0x67, 0x1A, 0x3A};// Este texto cifrado será el recibido en la transmisión



// Función para desencriptar un texto
void decryptText(const byte *key, const byte *iv, const byte *ciphertext, size_t size) {
    unsigned long start;
    unsigned long elapsed;
    int count;

    start = micros();
    for (count = 0; count < 500; ++count) { // Hace 500 asignaciones de claves y vectores de inicio para medir el tiempo como un promedio
    // Establece la clave y el vector de inicialización
    chacha.setKey(key, 32);
    chacha.setIV(iv, chacha.ivSize());
    }
    elapsed = micros() - start;
    Serial.print(elapsed / 500.0); // Tiempo promedio que le tarda asignar las claves y el IV
    Serial.print("us en asignación de clave e IV, ");
    Serial.print((500.0 * 1000000.0) / elapsed);
    Serial.println(" asignaciones por segundo");

    // Buffer para el texto desencriptado
    char* decryptedText = new char[size];

    start = micros();
    for (count = 0; count < 500; ++count) { // Descifra el texto 500 veces y con esto se espera obtener varias muestras de tiempo 
    // Desencripta el texto
    chacha.decrypt((byte *)decryptedText, ciphertext, size);
    }

    elapsed = micros() - start;
    Serial.print(elapsed / (size * 500.0)); // Tiempo promedio que tarda en descifrar 
    Serial.print("us por byte descifrado, ");
    Serial.print((size * 500.0 * 1000000.0) / elapsed);
    Serial.println(" bytes descifrados por segundo");

    // Imprime el texto desencriptado en formato de cadena de texto
    Serial.print("Texto desencriptado: \"");
    Serial.print(decryptedText);
    Serial.println("\"");

}

void setup() {
    Serial.begin(115200);

    size_t size = sizeof(cipherText);

    // Desencriptar el texto con la clave de 128 bits
    decryptText(key256, iv, cipherText, size);

}

void loop() {

}
