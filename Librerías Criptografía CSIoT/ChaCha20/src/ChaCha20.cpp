// ChaCha20.cpp
#include "ChaCha20.h"
#include <string.h> // memcpy


// rotate left seguro para 32-bit
static inline uint32_t rotl(uint32_t x, int n) {
    return (x << n) | (x >> (32 - n));
}

ChaCha20::ChaCha20(){
    
}

// Función Quarter Round para ChaCha20 (usa rotl para seguridad en AVR)
void ChaCha20::quarter_round(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d) {
    a = (a + b);
    d ^= a;
    d = rotl(d, 16);

    c = (c + d);
    b ^= c;
    b = rotl(b, 12);

    a = (a + b);
    d ^= a;
    d = rotl(d, 8);

    c = (c + d);
    b ^= c;
    b = rotl(b, 7);
}

// Convierte un arreglo de bytes en palabras de 32 bits
void ChaCha20::bytes_to_words(const uint8_t *byte_array, uint32_t *words, size_t length) {
    // length debe ser múltiplo de 4
    for (size_t i = 0; i < length / 4; i++) {
        // Forzar promoción a uint32_t antes de desplazar — importantísimo en AVR
        words[i] = ((uint32_t)byte_array[4 * i]) |
                   ((uint32_t)byte_array[4 * i + 1] << 8) |
                   ((uint32_t)byte_array[4 * i + 2] << 16) |
                   ((uint32_t)byte_array[4 * i + 3] << 24);
    }
}

// Convierte palabras de 32 bits en un arreglo de bytes
void ChaCha20::words_to_bytes(const uint32_t *words, uint8_t *byte_array, size_t length) {
    for (size_t i = 0; i < length / 4; i++) {
        byte_array[4 * i]     = (uint8_t)(words[i] & 0xFF);
        byte_array[4 * i + 1] = (uint8_t)((words[i] >> 8) & 0xFF);
        byte_array[4 * i + 2] = (uint8_t)((words[i] >> 16) & 0xFF);
        byte_array[4 * i + 3] = (uint8_t)((words[i] >> 24) & 0xFF);
    }
}

// Genera un bloque ChaCha20
void ChaCha20::chacha20_block(const uint8_t *key, uint32_t counter, const uint8_t *nonce, uint8_t *output) {
    // Constantes
    const uint32_t constants[4] = {
        0x61707865, // "expand 32-byte k"
        0x3320646E,
        0x79622D32,
        0x6B206574
    };

    // Dividir clave y nonce en palabras de 32 bits
    uint32_t key_words[8];
    uint32_t nonce_words[3];
    bytes_to_words(key, key_words, 32);
    bytes_to_words(nonce, nonce_words, 12);

    // Construir matriz inicial
    uint32_t state[16] = {
        constants[0], constants[1], constants[2], constants[3],
        key_words[0], key_words[1], key_words[2], key_words[3],
        key_words[4], key_words[5], key_words[6], key_words[7],
        counter, nonce_words[0], nonce_words[1], nonce_words[2]
    };

    // Copia del estado para el procesamiento
    uint32_t working_state[16];
    memcpy(working_state, state, sizeof(state));

    // 20 rondas alternando columnas y diagonales
    for (int i = 0; i < 10; i++) {
        // Columnas
        quarter_round(working_state[0], working_state[4], working_state[8], working_state[12]);
        quarter_round(working_state[1], working_state[5], working_state[9], working_state[13]);
        quarter_round(working_state[2], working_state[6], working_state[10], working_state[14]);
        quarter_round(working_state[3], working_state[7], working_state[11], working_state[15]);

        // Diagonales
        quarter_round(working_state[0], working_state[5], working_state[10], working_state[15]);
        quarter_round(working_state[1], working_state[6], working_state[11], working_state[12]);
        quarter_round(working_state[2], working_state[7], working_state[8], working_state[13]);
        quarter_round(working_state[3], working_state[4], working_state[9], working_state[14]);
    }

    // Sumar estado inicial y final
    for (int i = 0; i < 16; i++) {
        working_state[i] = (working_state[i] + state[i]);
    }

    // Convertir a bytes
    words_to_bytes(working_state, output, 64);
}

// Cifra un mensaje usando ChaCha20
void ChaCha20::chacha20_encrypt(const uint8_t *key, const uint8_t *nonce, uint32_t counter, const uint8_t *plaintext, size_t length, uint8_t *ciphertext) {
    uint8_t keystream[64];

    for (size_t i = 0; i < length; i += 64) {
        chacha20_block(key, counter++, nonce, keystream);
        for (size_t j = 0; j < 64 && i + j < length; j++) {
            ciphertext[i + j] = plaintext[i + j] ^ keystream[j];
        }
    }
}

void ChaCha20::chacha20_decrypt(const uint8_t *key, const uint8_t *nonce, uint32_t counter, const uint8_t *ciphertext, size_t length, uint8_t *decryptedText) {
    // The decryption process is identical to encryption in ChaCha20
    chacha20_encrypt(key, nonce, counter, (const uint8_t *)ciphertext, length, decryptedText);
}
