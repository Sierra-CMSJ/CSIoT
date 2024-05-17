
#include <Crypto.h>
#include <ChaCha.h>

// Define la instancia de ChaCha
ChaCha chacha;

// Clave y vector de inicialización
byte key256[32] = {0X9B, 0XA2, 0X1F, 0XC6, 0XB2, 0XCA, 0XF5, 0XDF, 0XFE, 0X43, 0X21, 0X60, 0X96, 0X56, 0XD3, 0X53, 0X25, 0X2D,
 0X7A, 0X9E, 0X4C, 0XCF, 0X11, 0XD2, 0X3A, 0X94, 0XF4, 0X89, 0X53, 0X82, 0X07, 0X83}; // Esta clave será la misma con la que se cifró la información
byte iv[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// Texto cifrado
byte cipherText[] = {0XD6, 0X22, 0X77, 0XD8, 0XF4, 0X7B, 0X74, 0XC1, 0XDE, 0X1E, 0X65, 0X0D, 0X8A, 0XE7, 0XE8, 0XF2};// Este texto cifrado será el recibido en la transmisión



// Función para desencriptar un texto
void decryptText(const byte *key, const byte *iv, const byte *ciphertext, size_t size) {
    unsigned long start;
    unsigned long elapsed;
    int count;

    // Buffer para el texto desencriptado
    char* decryptedText = new char[size];

    start = micros();
    for (count = 0; count < 500; ++count) { // Descifra el texto 500 veces y con esto se espera obtener varias muestras de tiempo 
    // Establece la clave y el vector de inicialización
    chacha.setKey(key, 32);
    chacha.setIV(iv, chacha.ivSize());
    // Desencripta el texto
    chacha.decrypt((byte *)decryptedText, ciphertext, size);
    }

    elapsed = micros() - start;
    Serial.print(elapsed / (size * 500.0)); // Tiempo promedio que tarda en descifrar 
    Serial.print("us por byte descifrado, ");
    Serial.print((size * 500.0 * 1000000.0) / elapsed);
    Serial.println(" bytes descifrados por segundo");

    // Evitamos caracteres de relleno
    decryptedText[size] = '\0'; // Agrega el carácter nulo al final de la cadena esto detiene el proceso e imprime solo la información importante

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
