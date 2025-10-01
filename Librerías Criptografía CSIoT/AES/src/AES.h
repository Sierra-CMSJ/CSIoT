#ifndef AES_H
#define AES_H
#include "arduino.h"

#if defined(__AVR__)  // Para plataformas AVR como Arduino Uno, Mega, etc.
    #include <avr/pgmspace.h>
#elif defined(ESP32)  // Para ESP32
    #include <pgmspace.h>
#elif defined(ARDUINO_ARCH_STM32)  // Para STM32
    // STM32 maneja la memoria flash de manera diferente, puedes omitir pgmspace.h
    // Aquí no necesitas incluir ningún archivo adicional.
#elif defined(ARDUINO_ARCH_RP2040)  // Para Raspberry Pi Pico (RP2040)
    #include <pgmspace.h>
#else
    #warning "Plataforma no soportada para PROGMEM. Considera una adaptación."
#endif

class AES{             
    public:
        // Declaraciones de las funciones
        AES();
        void keyExpansion(const uint8_t* key, int keySize, uint8_t* expandedKey);
        void encryptCBC(uint8_t* plainText, int length, uint8_t* roundKeys, int keySize, uint8_t* iv, uint8_t* cipherText);
        void decryptCBC(uint8_t* cipherText, int length, uint8_t* roundKeys, int keySize, uint8_t* iv, uint8_t* plainText);
        //////////
    private:
        static const uint8_t SBOX[256];
        static const uint8_t INV_SBOX[256];
        static const uint8_t RCON[10];
        void subWord(uint8_t* word);
        void rotWord(uint8_t* word);
        void textToState(const uint8_t* text, uint8_t state[4][4]);
        void stateToText(const uint8_t state[4][4], uint8_t* text);
        uint8_t mulBy02(uint8_t byte);
        uint8_t mulBy03(uint8_t byte);
        uint8_t mulBy09(uint8_t byte);
        uint8_t mulBy0B(uint8_t byte);
        uint8_t mulBy0D(uint8_t byte);
        uint8_t mulBy0E(uint8_t byte);
        void addRoundKey(uint8_t state[4][4], const uint8_t* roundKey);
        void subBytes(uint8_t state[4][4]);
        void invSubBytes(uint8_t state[4][4]);
        void shiftRows(uint8_t state[4][4]);
        void invShiftRows(uint8_t state[4][4]);
        void mixColumns(uint8_t state[4][4]);
        void invMixColumns(uint8_t state[4][4]);
        void encryptBlock(uint8_t* plainText, uint8_t* roundKeys, int keySize, uint8_t* cipherText);
        void decryptBlock(uint8_t* cipherText, uint8_t* roundKeys, int keySize, uint8_t* plainText);
        void xorBlocks(uint8_t* block1, const uint8_t* block2, int size);
};

#endif