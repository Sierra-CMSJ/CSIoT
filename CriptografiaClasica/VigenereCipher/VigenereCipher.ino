const char plaintext[] = "APVCMSJ2024IOTTG";
const char key[] = "APV"; // La clave puede contener letras y números
const int alphabetSize = 62;

void setup() {
  Serial.begin(115200);
  char ciphertext[sizeof(plaintext)];
  char decryptedtext[sizeof(plaintext)];
  
  encryptVigenere(plaintext, ciphertext, key);
  decryptVigenere(ciphertext, decryptedtext, key);
  
  Serial.print("Texto plano: ");
  Serial.println(plaintext);
  Serial.print("Texto cifrado: ");
  Serial.println(ciphertext);
  Serial.print("Texto descifrado: ");
  Serial.println(decryptedtext);
}

void loop() {
  // No se requiere código en el loop para este ejemplo.
}

void encryptVigenere(const char* plain, char* cipher, const char* key) {
  int keyLength = strlen(key);
  for (int i = 0; plain[i] != '\0'; i++) {
    if (isAlphaNumeric(plain[i])) {
      int plainIndex = getIndex(plain[i]);
      int keyIndex = getIndex(key[i % keyLength]);
      int newIndex = (plainIndex + keyIndex) % alphabetSize;
      cipher[i] = getCharFromIndex(newIndex);
    } else {
      cipher[i] = plain[i]; // No cambiar caracteres que no sean alfanuméricos
    }
  }
  cipher[strlen(plain)] = '\0'; // Añadir el carácter de fin de cadena
}

void decryptVigenere(const char* cipher, char* plain, const char* key) {
  int keyLength = strlen(key);
  for (int i = 0; cipher[i] != '\0'; i++) {
    if (isAlphaNumeric(cipher[i])) {
      int cipherIndex = getIndex(cipher[i]);
      int keyIndex = getIndex(key[i % keyLength]);
      int newIndex = (cipherIndex - keyIndex + alphabetSize) % alphabetSize;
      plain[i] = getCharFromIndex(newIndex);
    } else {
      plain[i] = cipher[i]; // No cambiar caracteres que no sean alfanuméricos
    }
  }
  plain[strlen(cipher)] = '\0'; // Añadir el carácter de fin de cadena
}

bool isAlphaNumeric(char c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}

int getIndex(char c) {
  if (c >= 'A' && c <= 'Z') return c - 'A'; // Índice de 0 a 25 para 'A'-'Z'
  if (c >= 'a' && c <= 'z') return c - 'a' + 26; // Índice de 26 a 51 para 'a'-'z'
  if (c >= '0' && c <= '9') return c - '0' + 52; // Índice de 52 a 61 para '0'-'9'
  return -1; // No debería suceder para caracteres alfanuméricos
}

char getCharFromIndex(int index) {
  if (index >= 0 && index < 26) return 'A' + index; // 'A'-'Z'
  if (index >= 26 && index < 52) return 'a' + (index - 26); // 'a'-'z'
  if (index >= 52 && index < 62) return '0' + (index - 52); // '0'-'9'
  return '?'; // No debería suceder para índices válidos
}
