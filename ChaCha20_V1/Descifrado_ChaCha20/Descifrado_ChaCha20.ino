
#include <Crypto.h>
#include <ChaCha.h>

// Define la instancia de ChaCha
ChaCha chacha;

// Clave y vector de inicialización
byte key256[32] = {0X50, 0X19, 0X86, 0X4A, 0X47, 0XD3, 0X2D, 0X45, 0X65, 0X79, 0X42, 0X43, 0X30, 0X8D, 0X45, 0X68, 0X15, 0XE4, 0X31, 0X7C, 0XC3, 0X94,
0X49, 0X5A, 0X72, 0XF1, 0XAE, 0XD0, 0X72, 0X90, 0X29, 0XF6}; // Esta clave será la misma con la que se cifró la información
byte iv[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// Texto cifrado
byte cipherText[] = {0X4E, 0X7D, 0X8B, 0X8F, 0XF7, 0X00, 0X49, 0X14, 0X56, 0X4B, 0X40, 0X18, 0X85, 0XF5, 0XDA, 0X18, 0X74, 0X5F, 0XAB, 0X5E, 0X87, 0X80, 0XDB, 0XEA,
0X7C, 0X6D, 0X82, 0XB6, 0XE3, 0XB2, 0XEE, 0XA5, 0X76, 0X61, 0XD9, 0X89, 0X2E, 0X64, 0XC8, 0X4D, 0X27, 0XE4, 0X6B, 0XC8, 0X2D, 0X7A, 0X1E, 0X84, 0X41, 0X57, 0XD9, 0X43, 0X8F,
0X62, 0XCB, 0XE8, 0X3A, 0X6C, 0X58, 0X85, 0XD3, 0XA6, 0X94, 0XF2, 0XEF, 0XD5, 0X0A, 0X74, 0X2D, 0XED, 0X46, 0X52, 0XEC, 0X4F, 0XEB, 0X6E, 0X3D, 0X7C, 0X80, 0X09, 0XD0, 0X03,
0X57, 0X67, 0X82, 0X33, 0X8F, 0XEA, 0XB6, 0XED, 0XBA, 0X1D, 0X24, 0XE1, 0X6B, 0X77, 0X5C, 0X98, 0X2E, 0X66, 0XF9, 0X21, 0X44, 0X5B, 0X7F, 0X3A, 0X66, 0X36, 0X81, 0XDD, 0XDE,
0XC2, 0X58, 0XA2, 0X30, 0X87, 0XEA, 0X62, 0XB9, 0XF4, 0X83, 0XC4, 0X0C, 0X7E, 0XEC, 0X0F, 0X07, 0X5C, 0XF3, 0X9A, 0X24};// Este texto cifrado será el recibido en la transmisión



// Función para desencriptar un texto
void decryptText(const byte *key, const byte *iv, const byte *ciphertext, size_t size) {
    // Establece la clave y el vector de inicialización
    chacha.setKey(key, 32);  // Asegúrate de que el tamaño de la clave sea 16 para una clave de 128 bits
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

    size_t size = sizeof(cipherText);

    // Desencriptar el texto con la clave de 128 bits
    decryptText(key256, iv, cipherText, size);

}

void loop() {

}
