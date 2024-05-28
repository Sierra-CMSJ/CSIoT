const char plaintext[] = "APVCMSJ2024IOTTG";
const int shift = 17; // Número de posiciones para desplazar
const int alphabetSize = 62;

void setup() {
  Serial.begin(115200);
  char ciphertext[sizeof(plaintext)];
  char decryptedtext[sizeof(plaintext)];
  char Ataque[sizeof(plaintext)];
  
  encryptCesar(plaintext, ciphertext, shift);
  decryptCesar(ciphertext, decryptedtext, shift);
  
  Serial.print("Texto plano: ");
  Serial.println(plaintext);
  Serial.print("Texto cifrado: ");
  Serial.println(ciphertext);
  Serial.print("Texto descifrado: ");
  Serial.println(decryptedtext);

  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();

  // Iterar sobre todas las posibles claves
  for(int key = 0; key < 62; key++) { // 26 letras mayúsculas + 26 letras minúsculas + 10 dígitos
    // Descifrar el texto con la clave actual
    decryptCesar(ciphertext, Ataque, key);
    
    // Imprimir el texto descifrado y la clave actual
    Serial.print("Clave ");
    Serial.print(key);
    Serial.print(": ");
    Serial.println(Ataque);
  }
}

void loop() {
  // No se requiere código en el loop para este ejemplo.
}

void encryptCesar(const char* plain, char* cipher, int shift) {
  int i = 0;
  while (plain[i] != '\0') {
    if (isAlphaNumeric(plain[i])) {
      int index = getIndex(plain[i]);
      int newIndex = (index + shift) % alphabetSize;
      cipher[i] = getCharFromIndex(newIndex);
    } else {
      cipher[i] = plain[i]; // No cambiar caracteres que no sean alfanuméricos
    }
    i++;
  }
  cipher[i] = '\0'; // Añadir el carácter de fin de cadena
}

void decryptCesar(const char* cipher, char* plain, int shift) {
  int i = 0;
  while (cipher[i] != '\0') {
    if (isAlphaNumeric(cipher[i])) {
      int index = getIndex(cipher[i]);
      int newIndex = (index - shift + alphabetSize) % alphabetSize; // Ajuste para evitar negativos
      plain[i] = getCharFromIndex(newIndex);
    } else {
      plain[i] = cipher[i]; // No cambiar caracteres que no sean alfanuméricos
    }
    i++;
  }
  plain[i] = '\0'; // Añadir el carácter de fin de cadena
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