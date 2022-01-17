#include <desklab.h>

const int clockPin = 3;
const int dataPin = 4;

void setup() {
  setupOUTConnection(dataPin, clockPin);
}


void loop() {
  char input = 'H';
  byte8_t bitsequence;
  bitsequence = encode(input);
  bitsequence = parity(bitsequence);
  display("H: ");
  sendByte(bitsequence, true, 5);
  delay(1000);
  clearDisplay();
  delay(1000);

  input = 'E';
  bitsequence = encode(input);
  bitsequence  = parity(bitsequence);
  display("E: ");
  sendByte(bitsequence, true, 5);
  delay(1000);
  clearDisplay();
  delay(1000);
  
  input = 'L';
  bitsequence = encode(input);
  bitsequence = parity(bitsequence);
  display("L: ");
  sendByte(bitsequence, true, 5);
  delay(1000);
  clearDisplay();
  delay(1000);
  display("L: ");
  sendByte(bitsequence, true, 5);
  delay(1000);
  clearDisplay();
  delay(1000);

  input = 'O';
  bitsequence = encode(input);
  bitsequence = parity(bitsequence);
  display("O: ");
  sendByte(bitsequence, true, 5);
  delay(1000);
  clearDisplay();
  delay(1000);

  delay(4000);
}
