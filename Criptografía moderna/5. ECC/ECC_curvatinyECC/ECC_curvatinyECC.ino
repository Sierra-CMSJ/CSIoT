#include <tinyECC.h>
tinyECC ecc;
void setup() {
  Serial.begin(115200);
  while(!Serial){
  // Espera que el monitor serial se inicie
  }
  unsigned long start;
  unsigned long elapsed;

  // Medición del tiempo de construccion de curva
  start = micros();
  for(int count=0; count<500; ++count){
  tinyECC ecc; // Se crea el objeto ecc llamando el constructor de la biblioteca
  }
  elapsed = micros() - start;
  Serial.print(elapsed / 500.0); // Tiempo promedio
  Serial.print("us estableciendo claves y puntos en la curva");
  Serial.println();

  ecc.plaintext="APVCMSJ2024IOTTG";
  Serial.println("Texto Plano: "+ecc.plaintext);
  // Tamaño del texto
  size_t size = strlen(ecc.plaintext.c_str());

  // Medición del tiempo de cifrado
  start = micros();
  for(int count=0; count < 500; ++count){
    ecc.encrypt();
  }
  elapsed = micros() - start;
  Serial.print(elapsed / (size * 500.0)); // Tiempo promedio que tarda en cifrar 
  Serial.print("us por byte cifrado, ");
  Serial.print((size * 500.0 * 1000000.0) / elapsed);
  Serial.println(" bytes cifrados por segundo");
  Serial.println("Texto Cifrado: "+ecc.ciphertext);

  String cipher = ecc.ciphertext;
  ecc.ciphertext = "";

  // Tamaño del texto cifrado
  size_t sizecipher = strlen(cipher.c_str());

  // Medición del tiempo de descifrado
  start = micros();
  for(int count=0; count < 500; ++count){
    ecc.ciphertext = cipher;
    ecc.decrypt();
  }
  elapsed = micros() - start;
  Serial.print(elapsed / (sizecipher * 500.0)); // Tiempo promedio que tarda en descifrar 
  Serial.print("us por byte descifrado, ");
  Serial.print((sizecipher * 500.0 * 1000000.0) / elapsed);
  Serial.println(" bytes descifrados por segundo");
  Serial.println("Decodificado: "+ecc.plaintext);
}

void loop() {
}
