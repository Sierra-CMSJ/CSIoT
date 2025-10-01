#ifndef SHA256_H
#define SHA256_H

#include <Arduino.h>

class SHA256 {
public:
    SHA256();
    void update(const uint8_t *data, uint32_t len);
    void final(uint8_t hash[32]);
    void hash(const char *text, uint8_t hash[32]);

private:
    void transform(const uint8_t data[64]);
    void init();
    uint32_t rightRotate(uint32_t value, unsigned int count);

    uint32_t state[8];   // Estado interno (8 x 32 = 256 bits)
    uint64_t bitlen;     // Longitud total del mensaje en bits
    uint8_t data[64];    // Buffer de 512 bits (64 bytes)
    uint32_t datalen;    // Cantidad de bytes actualmente en el buffer
};

#endif // SHA256_H
