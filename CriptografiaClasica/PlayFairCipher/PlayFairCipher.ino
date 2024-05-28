#include <Arduino.h>

// Tamaño del tablero del cifrado Playfair
#define SIZE 6

// Clave para el cifrado Playfair
const char key[] = "CRIPTOGRAFIA2024";

// Tablero de cifrado
char table[SIZE][SIZE];

// Función para eliminar caracteres duplicados en una cadena
void removeDuplicates(char* str) {
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    for (int j = i + 1; j < len; j++) {
      if (str[i] == str[j]) {
        for (int k = j; k < len; k++) {
          str[k] = str[k + 1];
        }
        len--;
        j--;
      }
    }
  }
}

// Función para crear el tablero de cifrado Playfair
void createTable() {
  char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"; // Alfabeto extendido
  bool used[36] = {0}; // Arreglo de booleanos para marcar los caracteres usados
  int x = 0, y = 0;

  // Eliminar duplicados en la clave
  char keyCopy[strlen(key) + 1];
  strcpy(keyCopy, key);
  removeDuplicates(keyCopy);

  // Llenar la tabla con la clave
  for (int i = 0; keyCopy[i] != '\0'; i++) {
    char ch = keyCopy[i];
    int index;
    if (ch >= 'A' && ch <= 'Z') {
      index = ch - 'A'; // Índice para letras
    } else if (ch >= '0' && ch <= '9') {
      index = ch - '0' + 26; // Índice para dígitos
    } else {
      continue; // Ignorar caracteres que no sean letras o dígitos
    }

    if (!used[index]) {
      table[y][x++] = ch;
      used[index] = true;
      if (x == SIZE) {
        x = 0;
        y++;
      }
    }
  }

  // Llenar la tabla con el resto del alfabeto
  for (int i = 0; alphabet[i] != '\0'; i++) {
    char ch = alphabet[i];
    int index;
    if (ch >= 'A' && ch <= 'Z') {
      index = ch - 'A';
    } else if (ch >= '0' && ch <= '9') {
      index = ch - '0' + 26;
    } else {
      continue;
    }

    if (!used[index]) {
      table[y][x++] = ch;
      used[index] = true;
      if (x == SIZE) {
        x = 0;
        y++;
      }
    }
  }
}

// Función para encontrar la posición de un carácter en la matriz
void findPosition(char ch, int& row, int& col) {
  for (row = 0; row < SIZE; row++) {
    for (col = 0; col < SIZE; col++) {
      if (table[row][col] == ch) {
        return;
      }
    }
  }
}

// Función para cifrar un par de caracteres
void encryptPair(char& a, char& b) {
  int row1, col1, row2, col2;
  findPosition(a, row1, col1);
  findPosition(b, row2, col2);

  if (row1 == row2) {
    col1 = (col1 + 1) % SIZE;
    col2 = (col2 + 1) % SIZE;
  } else if (col1 == col2) {
    row1 = (row1 + 1) % SIZE;
    row2 = (row2 + 1) % SIZE;
  } else {
    int temp = col1;
    col1 = col2;
    col2 = temp;
  }

  a = table[row1][col1];
  b = table[row2][col2];
}

// Función para descifrar un par de caracteres
void decryptPair(char& a, char& b) {
  int row1, col1, row2, col2;
  findPosition(a, row1, col1);
  findPosition(b, row2, col2);

  if (row1 == row2) {
    col1 = (col1 - 1 + SIZE) % SIZE;
    col2 = (col2 - 1 + SIZE) % SIZE;
  } else if (col1 == col2) {
    row1 = (row1 - 1 + SIZE) % SIZE;
    row2 = (row2 - 1 + SIZE) % SIZE;
  } else {
    int temp = col1;
    col1 = col2;
    col2 = temp;
  }

  a = table[row1][col1];
  b = table[row2][col2];
}

// Función para cifrar el texto plano
void encryptText(const char* plaintext, char* ciphertext) {
  int len = strlen(plaintext);
  for (int i = 0; i < len; i += 2) {
    char a = plaintext[i];
    char b = (i + 1 < len) ? plaintext[i + 1] : 'X'; // Usar 'X' si no hay pareja

    // Si los caracteres son iguales, reemplazar el segundo por 'X'
    if (a == b) {
      b = 'X';
    }

    encryptPair(a, b);

    ciphertext[i] = a;
    ciphertext[i + 1] = b;
  }
  ciphertext[len] = '\0'; // Asegurarse de que el texto cifrado esté terminado correctamente
}

// Función para descifrar el texto cifrado
void decryptText(const char* ciphertext, char* plaintext) {
  int len = strlen(ciphertext);
  for (int i = 0; i < len; i += 2) {
    char a = ciphertext[i];
    char b = ciphertext[i + 1];

    decryptPair(a, b);

    plaintext[i] = a;
    plaintext[i + 1] = b;
  }
  plaintext[len] = '\0'; // Asegurarse de que el texto descifrado esté terminado correctamente
}

void setup() {
  Serial.begin(115200);

  // Crear el tablero de cifrado
  createTable();

  // Mostrar el tablero de cifrado
  Serial.println("Playfair Table:");
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      Serial.print(table[i][j]);
      Serial.print(" ");
    }
    Serial.println();
  }

  // Texto plano y variables para cifrado y descifrado
  const char plaintext[] = "APVCMSJ2024IOTTG";
  char ciphertext[100];
  char decryptedText[100];

  // Mostrar el texto plano
  Serial.print("Plaintext: ");
  Serial.println(plaintext);

  // Cifrar el texto plano
  encryptText(plaintext, ciphertext);

  // Mostrar el texto cifrado
  Serial.print("Ciphertext: ");
  Serial.println(ciphertext);

  // Descifrar el texto cifrado
  decryptText(ciphertext, decryptedText);

  // Mostrar el texto descifrado
  Serial.print("Decrypted Text: ");
  Serial.println(decryptedText);
}

void loop() {
  // No necesitamos hacer nada en el loop
}

