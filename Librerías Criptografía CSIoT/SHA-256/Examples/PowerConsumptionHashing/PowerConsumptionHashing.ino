#include <SHA256.h>

const unsigned long interval_us = 3000;   // Intervalo en microsegundos

const int plainTextSize = 64;
//const char plain_Text[] =     //16
//"XGTRMZPLQHADCEYA";

const char plain_Text[] =     //64
"XGTRMZPLQHADCEYAXGTRMZPLQHADCEYAXGTRMZPLQHADCEYAXGTRMZPLQHADCEYA";

//const char plain_Text[] =     //128
//"XGTRMZPLQHADCEYAXGTRMZPLQHADCEYAXGTRMZPLQHADCEYAXGTRMZPLQHADCEYAXGTRMZPLQHADCEYAXGTRMZPLQHADCEYAXGTRMZPLQHADCEYAXGTRMZPLQHADCEYA";

//const char plain_Text[] =     //256
//"XGTRMZPLQHADCEYAXGTRMZPLQHADCEYAXGTRMZPLQHADCEYAXGTRMZPLQHADCEYAXGTRMZPLQHADCEYAXGTRMZPLQHADCEYAXGTRMZPLQHADCEYAXGTRMZPLQHADCEYA"
//"XGTRMZPLQHADCEYAXGTRMZPLQHADCEYAXGTRMZPLQHADCEYAXGTRMZPLQHADCEYAXGTRMZPLQHADCEYAXGTRMZPLQHADCEYAXGTRMZPLQHADCEYAXGTRMZPLQHADCEYA";


SHA256 sha256; // Llamada al constructor
 
uint8_t hash[32];

void setup() {
  Serial.begin(115200);
  //while(!Serial);
}

void loop() {
  for (int i = 0; i < 10; i++) {
    sha256.hash(plain_Text, hash);
  }

  /*
  Serial.print("Hash (SHA256): ");
  for (int i = 0; i < 32; ++i) {
    if (hash[i] < 0x10) Serial.print("0");
    Serial.print(hash[i], HEX);
  }
  Serial.println();
  */

  // Espera fija de en µs
  delayMicroseconds(interval_us);
}