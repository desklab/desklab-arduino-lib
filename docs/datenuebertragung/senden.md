---
hide:
  - toc
---

# Senden

```C++
#include <desklab.h>

const int clockPin = 3;
const int dataPin = 4;

void setup() {
  setupWriteConnection(dataPin, clockPin);
}


void loop() {
  char input = 'H';
  byte8_t bitsequence;
  bitsequence = encode(input);
  bitsequence = parity(bitsequence);
  display("H: ");
  writeByte(bitsequence, true);
  delay(1000);
  clearDisplay();
  delay(1000);

  input = 'E';
  bitsequence = encode(input);
  bitsequence  = parity(bitsequence);
  display("E: ");
  writeByte(bitsequence, true);
  delay(1000);
  clearDisplay();
  delay(1000);
  
  input = 'L';
  bitsequence = encode(input);
  bitsequence = parity(bitsequence);
  display("L: ");
  writeByte(bitsequence, true);
  delay(1000);
  clearDisplay();
  delay(1000);
  display("L: ");
  writeByte(bitsequence, true);
  delay(1000);
  clearDisplay();
  delay(1000);

  input = 'O';
  bitsequence = encode(input);
  bitsequence = parity(bitsequence);
  display("O: ");
  writeByte(bitsequence, true);
  delay(1000);
  clearDisplay();
  delay(1000);

  delay(4000);
}
```