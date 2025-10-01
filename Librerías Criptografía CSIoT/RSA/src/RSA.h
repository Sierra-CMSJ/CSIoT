#ifndef RSA_H 
#define RSA_H

class RSA {
public:
    RSA();
    void generate_keys(unsigned long p, unsigned long q, unsigned long &e, unsigned long &d, unsigned long &n);
    void encrypt_message(const char* plain_text, unsigned long e, unsigned long n, unsigned long long encrypted_message[], int length);
    void decrypt_message(unsigned long long encrypted_message[], int length, unsigned long d, unsigned long n, char decrypted_message[]);

    // Nueva función pública para encontrar e
    unsigned long findE(unsigned long phi_n);

private:
    bool is_prime(unsigned long n);
    unsigned long gcd(unsigned long a, unsigned long b);
    unsigned long mod_inverse(unsigned long e, unsigned long phi);
    unsigned long mod_exp(unsigned long long base, unsigned long exp, unsigned long mod);
};

#endif // RSA_H

