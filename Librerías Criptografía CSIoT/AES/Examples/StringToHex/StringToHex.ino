void setup() {
  Serial.begin(115200);

  // Cadena de ejemplo
  String texto = "Criptografia1234";

  Serial.print("Texto original: ");
  Serial.println(texto);

  Serial.print("En hexadecimal: ");
  imprimirHex(texto);
}

void loop() {
  // No se usa en este ejemplo
}

void imprimirHex(String str) {
  for (int i = 0; i < str.length(); i++) {
    // Imprime en formato 0xXX
    Serial.print("0x");
    if (str[i] < 16) Serial.print("0"); // para mantener siempre 2 dígitos
    Serial.print(str[i], HEX);

    if (i < str.length() - 1) {
      Serial.print(","); // separador entre bytes
    }
  }
  Serial.println();
}
