#ifndef CHACHA20_H
#define CHACHA20_H

#include <Arduino.h>
#include <stdint.h>
#include <stddef.h>

class ChaCha20 {
  public:
    ChaCha20();  

    /**
     * @brief Cifra un mensaje con ChaCha20
     * @param key        Clave de 32 bytes
     * @param nonce      Nonce de 12 bytes
     * @param counter    Contador inicial (32 bits)
     * @param plaintext  Texto plano a cifrar
     * @param length     Longitud del texto plano en bytes
     * @param ciphertext Buffer de salida con el texto cifrado
     */
    void chacha20_encrypt(const uint8_t *key, const uint8_t *nonce, uint32_t counter,
                          const uint8_t *plaintext, size_t length, uint8_t *ciphertext);

    /**
     * @brief Descifra un mensaje con ChaCha20
     * @param key           Clave de 32 bytes
     * @param nonce         Nonce de 12 bytes
     * @param counter       Contador inicial (32 bits)
     * @param ciphertext    Texto cifrado a descifrar
     * @param length        Longitud del texto cifrado en bytes
     * @param decryptedText Buffer de salida con el texto plano
     */
    void chacha20_decrypt(const uint8_t *key, const uint8_t *nonce, uint32_t counter,
                          const uint8_t *ciphertext, size_t length, uint8_t *decryptedText);

  private:
    void quarter_round(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d);
    void bytes_to_words(const uint8_t *byte_array, uint32_t *words, size_t length);
    void words_to_bytes(const uint32_t *words, uint8_t *byte_array, size_t length);
    void chacha20_block(const uint8_t *key, uint32_t counter, const uint8_t *nonce, uint8_t *output);
};

#endif // CHACHA20_H
