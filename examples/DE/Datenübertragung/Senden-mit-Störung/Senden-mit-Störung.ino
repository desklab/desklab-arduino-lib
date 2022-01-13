#include <desklab.h>

const int clockPin = 3;
const int dataPin = 4;

void setup() {
  setupOUTConnection(dataPin, clockPin);
}


void loop() {
  char input = 'H';
  byte8_t H;
  H = encode(input);
  H = parity(H);
  display("H: ");
  sendByte(H, true, 5);
  delay(1000);
  clearDisplay();
  delay(1000);

  input = 'E';
  byte8_t E;
  E = encode(input);
  E = parity(E);
  display("E: ");
  sendByte(E, true, 30);
  delay(1000);
  clearDisplay();
  delay(1000);
  
  input = 'L';
  byte8_t L;
  L = encode(input);
  L = parity(L);
  display("L: ");
  sendByte(L, true, 5);
  delay(1000);
  clearDisplay();
  delay(1000);
  display("L: ");
  sendByte(L, true, 5);
  delay(1000);
  clearDisplay();
  delay(1000);

  input = 'O';
  byte8_t O;
  O = encode(input);
  O = parity(O);
  display("O: ");
  sendByte(O, true, 5);
  delay(1000);
  clearDisplay();
  delay(1000);

  delay(4000);
}
