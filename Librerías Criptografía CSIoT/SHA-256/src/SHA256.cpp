#include "SHA256.h"

// Constantes SHA-256 (primeros 32 bits de las fracciones de las raíces cúbicas de los primeros 64 primos)
static const uint32_t K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

SHA256::SHA256() {
    init();
}

void SHA256::init() {
    // Valores iniciales de SHA-256 (primeros 32 bits de las raíces cuadradas de los primeros 8 primos)
    state[0] = 0x6a09e667;
    state[1] = 0xbb67ae85;
    state[2] = 0x3c6ef372;
    state[3] = 0xa54ff53a;
    state[4] = 0x510e527f;
    state[5] = 0x9b05688c;
    state[6] = 0x1f83d9ab;
    state[7] = 0x5be0cd19;

    bitlen = 0;
    datalen = 0;
}

uint32_t SHA256::rightRotate(uint32_t value, unsigned int count) {
    return (value >> count) | (value << (32 - count));
}

void SHA256::transform(const uint8_t data[64]) {
    uint32_t m[64];
    uint32_t a, b, c, d, e, f, g, h;

    for (uint32_t i = 0, j = 0; i < 16; ++i, j += 4)
        m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);

    for (uint32_t i = 16; i < 64; ++i) {
        uint32_t s0 = rightRotate(m[i - 15], 7) ^ rightRotate(m[i - 15], 18) ^ (m[i - 15] >> 3);
        uint32_t s1 = rightRotate(m[i - 2], 17) ^ rightRotate(m[i - 2], 19) ^ (m[i - 2] >> 10);
        m[i] = m[i - 16] + s0 + m[i - 7] + s1;
    }

    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    e = state[4];
    f = state[5];
    g = state[6];
    h = state[7];

    for (uint32_t i = 0; i < 64; ++i) {
        uint32_t S1 = rightRotate(e, 6) ^ rightRotate(e, 11) ^ rightRotate(e, 25);
        uint32_t ch = (e & f) ^ ((~e) & g);
        uint32_t temp1 = h + S1 + ch + K[i] + m[i];
        uint32_t S0 = rightRotate(a, 2) ^ rightRotate(a, 13) ^ rightRotate(a, 22);
        uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
        uint32_t temp2 = S0 + maj;

        h = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
    }

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    state[5] += f;
    state[6] += g;
    state[7] += h;
}

void SHA256::update(const uint8_t *data, uint32_t len) {
    for (uint32_t i = 0; i < len; ++i) {
        this->data[datalen] = data[i];
        datalen++;
        if (datalen == 64) {
            transform(this->data);
            bitlen += 512;
            datalen = 0;
        }
    }
}

void SHA256::final(uint8_t hash[32]) {
    uint32_t i = datalen;

    // Padding
    if (datalen < 56) {
        data[i++] = 0x80;
        while (i < 56) data[i++] = 0x00;
    } else {
        data[i++] = 0x80;
        while (i < 64) data[i++] = 0x00;
        transform(data);
        memset(data, 0, 56);
    }

    bitlen += datalen * 8;
    data[63] = bitlen;
    data[62] = bitlen >> 8;
    data[61] = bitlen >> 16;
    data[60] = bitlen >> 24;
    data[59] = bitlen >> 32;
    data[58] = bitlen >> 40;
    data[57] = bitlen >> 48;
    data[56] = bitlen >> 56;
    transform(data);

    for (i = 0; i < 4; ++i) {
        for (uint32_t j = 0; j < 8; ++j) {
            hash[i + (j * 4)] = (state[j] >> (24 - i * 8)) & 0x000000ff;
        }
    }
}

void SHA256::hash(const char *text, uint8_t hash[32]) {
    init();  // 🔑 Reinicia el estado SIEMPRE
    update((const uint8_t*)text, strlen(text));
    final(hash);
}
