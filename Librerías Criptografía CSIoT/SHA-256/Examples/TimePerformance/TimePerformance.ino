#include <SHA256.h>

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
  unsigned long totalHashTime = 0;

  
  for (int i = 0; i < 100; i++) {
    unsigned long startEnc = micros();
    sha256.hash(plain_Text, hash);
    unsigned long endEnc = micros();
    totalHashTime += (endEnc - startEnc);
  }
  float avgHash = totalHashTime / 100.0;

  Serial.print("Hash (SHA256): ");
  for (int i = 0; i < 32; ++i) {
    if (hash[i] < 0x10) Serial.print("0");
    Serial.print(hash[i], HEX);
  }
  Serial.println();

    // Mostramos resultados
  Serial.println("=== RESULTADOS PROMEDIO ===");
  Serial.print("Tiempo promedio de Hashing (us): ");
  Serial.println(avgHash);

  // Mostramos resultados
  Serial.println("=== RESULTADOS PROMEDIO [Byte/us] ===");
  Serial.print("Tiempo promedio de Hashing [Byte/us]: ");
  Serial.println(avgHash/plainTextSize);

}

void loop() {
}