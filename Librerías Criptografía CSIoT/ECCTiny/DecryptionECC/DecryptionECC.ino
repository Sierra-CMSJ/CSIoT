#include <tinyECC.h>

tinyECC ecc;

void setup() {
  Serial.begin(115200);
  //while (!Serial);

  // Aquí pegas el resultado del archivo anterior
  ecc.ciphertext = "106,285,814,527,14,166,371,628,775,553,453,618,263,379,135,929,142,911,307,174,236,892,309,961,418,440,599,119,418,440,582,633,558,334,810,550,707,971,649,103,1,5,771,958,14,166,403,855,27,367,954,834,142,911,801,226,14,166,942,493";

  // Descifrar
  ecc.decrypt();
  
  /*
  Serial.println("Texto Descifrado: " + ecc.plaintext);
  */
}

void loop() {
  // Nada
}
