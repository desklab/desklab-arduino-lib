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
  clearDisplay();
  display("H: ");
  writeByte(bitsequence, true, 5);
  delay(500);

  input = 'E';
  bitsequence = encode(input);
  bitsequence  = parity(bitsequence);
  clearDisplay();
  display("E: ");
  writeByte(bitsequence, true, 5);
  delay(500);
  
  input = 'L';
  bitsequence = encode(input);
  bitsequence = parity(bitsequence);
  clearDisplay();
  display("L: ");
  writeByte(bitsequence, true, 5);
  delay(500);

  clearDisplay();
  display("L: ");
  writeByte(bitsequence, true, 5);
  delay(500);

  input = 'O';
  bitsequence = encode(input);
  bitsequence = parity(bitsequence);
  clearDisplay();
  display("O: ");
  writeByte(bitsequence, true, 5);
  delay(500);

  delay(4000);
}
