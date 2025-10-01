#include "AES.h"

// Definicion de las constantes

const uint8_t AES::SBOX[256] = {
  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

const uint8_t AES::INV_SBOX[256] = {
  0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
  0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
  0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
  0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
  0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
  0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
  0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
  0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
  0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
  0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
  0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
  0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
  0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
  0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
  0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
  0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
}; 

const uint8_t AES::RCON[10] = {
  0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36 
};

AES::AES() {
    // Constructor vacio
}

// Helper functions
void AES::subWord(uint8_t* word) {
    for (int i = 0; i < 4; i++) {
        word[i] = SBOX[word[i]];
    }
}

void AES::rotWord(uint8_t* word) {
    uint8_t temp = word[0];
    for (int i = 0; i < 3; i++) {
        word[i] = word[i + 1];
    }
    word[3] = temp;
}

void AES::keyExpansion(const uint8_t* key, int keySize, uint8_t* expandedKey) {
    int numWords;
    int aux;
    if(keySize == 16){
      numWords = 44;
      aux = 4;
    }
    else if(keySize == 24){
      numWords = 52;
      aux = 6;
    }
    else if(keySize == 32){
      numWords = 60;
      aux = 8;
    }

    // Inicializar con la clave
    memcpy(expandedKey, key, keySize);

    for (int i = aux; i < numWords; i++) {
        uint8_t temp[4];
        memcpy(temp, expandedKey + 4 * (i - 1), 4);

        if (i % aux == 0) {
            rotWord(temp);
            subWord(temp);
            temp[0] ^= RCON[i / aux - 1];
        } else if (i % aux == 4 && keySize == 32) {
            subWord(temp);  // Sustitución S-Box adicional para AES-256
        }

        for (int j = 0; j < 4; j++) {
            expandedKey[4 * i + j] = expandedKey[4 * (i - aux) + j] ^ temp[j];
        }
    }
}

void AES::textToState(const uint8_t* text, uint8_t state[4][4]) {
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            state[r][c] = text[r + 4 * c];
        }
    }
}

void AES::stateToText(const uint8_t state[4][4], uint8_t* text) {
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            text[r + 4 * c] = state[r][c];
        }
    }
}



uint8_t AES::mulBy02(uint8_t byte) {
    return (byte << 1) ^ (0x1B & -(byte >> 7));
}

uint8_t AES::mulBy03(uint8_t byte) {
    return mulBy02(byte) ^ byte;
}

uint8_t AES::mulBy09(uint8_t byte) {
    // 9 = 2^3 + 1
    return mulBy02(mulBy02(mulBy02(byte))) ^ byte;
}

uint8_t AES::mulBy0B(uint8_t byte) {
    // 11 = 2^3 + 2 + 1
    return mulBy02(mulBy02(mulBy02(byte))) ^ mulBy02(byte) ^ byte;
}

uint8_t AES::mulBy0D(uint8_t byte) {
    // 13 = 2^3 + 2^2 + 1
    return mulBy02(mulBy02(mulBy02(byte))) ^ mulBy02(mulBy02(byte)) ^ byte;
}

uint8_t AES::mulBy0E(uint8_t byte) {
    // 14 = 2^3 + 2^2 + 2
    return mulBy02(mulBy02(mulBy02(byte))) ^ mulBy02(mulBy02(byte)) ^ mulBy02(byte);
}

void AES::addRoundKey(uint8_t state[4][4], const uint8_t* roundKey) {
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            state[r][c] ^= roundKey[c * 4 + r];
        }
    }
}

void AES::subBytes(uint8_t state[4][4]) {
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            state[r][c] = SBOX[state[r][c]];
        }
    }
}

void AES::invSubBytes(uint8_t state[4][4]) {
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            state[r][c] = INV_SBOX[state[r][c]];
        }
    }
}

void AES::shiftRows(uint8_t state[4][4]) {
    for (int r = 1; r < 4; r++) {
        uint8_t temp[4];
        for (int c = 0; c < 4; c++) {
            temp[c] = state[r][(c + r) % 4];
        }
        memcpy(state[r], temp, 4);
    }
}

void AES::invShiftRows(uint8_t state[4][4]) {
    for (int r = 1; r < 4; r++) {
        uint8_t temp[4];
        for (int c = 0; c < 4; c++) {
            temp[c] = state[r][(c - r + 4) % 4];
        }
        memcpy(state[r], temp, 4);
    }
}

void AES::mixColumns(uint8_t state[4][4]) {
    for (int c = 0; c < 4; c++) {
        uint8_t a = state[0][c];
        uint8_t b = state[1][c];
        uint8_t c1 = state[2][c];
        uint8_t d = state[3][c];

        state[0][c] = mulBy02(a) ^ mulBy03(b) ^ c1 ^ d;
        state[1][c] = a ^ mulBy02(b) ^ mulBy03(c1) ^ d;
        state[2][c] = a ^ b ^ mulBy02(c1) ^ mulBy03(d);
        state[3][c] = mulBy03(a) ^ b ^ c1 ^ mulBy02(d);
    }
}

void AES::invMixColumns(uint8_t state[4][4]) {
    for (int c = 0; c < 4; c++) {
        uint8_t a = state[0][c];
        uint8_t b = state[1][c];
        uint8_t c1 = state[2][c];
        uint8_t d = state[3][c];

        state[0][c] = mulBy0E(a) ^ mulBy0B(b) ^ mulBy0D(c1) ^ mulBy09(d);
        state[1][c] = mulBy09(a) ^ mulBy0E(b) ^ mulBy0B(c1) ^ mulBy0D(d);
        state[2][c] = mulBy0D(a) ^ mulBy09(b) ^ mulBy0E(c1) ^ mulBy0B(d);
        state[3][c] = mulBy0B(a) ^ mulBy0D(b) ^ mulBy09(c1) ^ mulBy0E(d);
    }
}

void AES::encryptBlock(uint8_t* plainText, uint8_t* roundKeys, int keySize, uint8_t* cipherText) {
    uint8_t state[4][4];
    textToState(plainText, state);
    int rounds;
    int aux;
    if(keySize == 16){
      rounds = 10;
      aux = 160;
    }
    else if(keySize == 24){
      rounds = 12;
      aux = 192;
    }
    else if(keySize == 32){
      rounds = 14;
      aux = 224;
    }

    // Initial round
    addRoundKey(state, roundKeys);

    // Main rounds (14 rounds for AES-256)
    for (int round = 1; round < rounds; round++) {
        subBytes(state);
        shiftRows(state);
        mixColumns(state);
        addRoundKey(state, roundKeys + 16 * round);
    }

    // Final round
    subBytes(state);
    shiftRows(state);
    addRoundKey(state, roundKeys + aux); // 14 * 16 = 224

    stateToText(state, cipherText);
}

void AES::decryptBlock(uint8_t* cipherText, uint8_t* roundKeys, int keySize, uint8_t* plainText) {
    uint8_t state[4][4];
    textToState(cipherText, state);
    int rounds;
    int aux;
    if(keySize == 16){
      rounds = 9;
      aux = 160;
    }
    else if(keySize == 24){
      rounds = 11;
      aux = 192;
    }
    else if(keySize == 32){
      rounds = 13;
      aux = 224;
    }

    // Initial round
    addRoundKey(state, roundKeys + aux); // Última clave
    invShiftRows(state);
    invSubBytes(state);

    // Main rounds (14 rounds for AES-256)
    for (int round = rounds; round > 0; round--) {
        addRoundKey(state, roundKeys + 16 * round);
        invMixColumns(state);
        invShiftRows(state);
        invSubBytes(state);
    }

    // Final round
    addRoundKey(state, roundKeys);

    stateToText(state, plainText);
}

void AES::xorBlocks(uint8_t* block1, const uint8_t* block2, int size) {
    for (int i = 0; i < size; i++) {
        block1[i] ^= block2[i];
    }
}

void AES::encryptCBC(uint8_t* plainText, int length, uint8_t* roundKeys, int keySize, uint8_t* iv, uint8_t* cipherText) {
    uint8_t previousBlock[16];
    memcpy(previousBlock, iv, 16);

    for (int i = 0; i < length; i += 16) {
        uint8_t block[16];
        memcpy(block, plainText + i, 16);

        xorBlocks(block, previousBlock, 16);

        encryptBlock(block, roundKeys, keySize, cipherText + i);

        memcpy(previousBlock, cipherText + i, 16);
    }
}

void AES::decryptCBC(uint8_t* cipherText, int length, uint8_t* roundKeys, int keySize, uint8_t* iv, uint8_t* plainText) {
    uint8_t previousBlock[16];
    memcpy(previousBlock, iv, 16);

    for (int i = 0; i < length; i += 16) {
        uint8_t block[16];
        uint8_t decryptedBlock[16];

        // Obtener el bloque cifrado actual
        memcpy(block, cipherText + i, 16);

        // Descifrar el bloque
        decryptBlock(block, roundKeys, keySize, decryptedBlock);

        // XOR con el bloque anterior o el IV
        xorBlocks(decryptedBlock, previousBlock, 16);

        // Guardar el bloque descifrado en el texto plano
        memcpy(plainText + i, decryptedBlock, 16);

        // Actualizar el bloque previo
        memcpy(previousBlock, block, 16);
    }
}