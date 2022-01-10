#include <desklab.h>

int clockPin = 3;
int dataPin = 4;

void setup() {
  setupOUTConnection(dataPin, clockPin);
}


void loop() {
  byte8_t H;
  H = encode('H');
  H = parity(H);
  sendByte(H, true);

  byte8_t E;
  E = encode('E');
  E = parity(E);   
  sendByte(E, true);
  
  byte8_t L;
  L = encode('L');
  L = parity(L); 
  sendByte(L, true);
  sendByte(L, true);

  byte8_t O;
  O = encode('O');
  O = parity(O);
  sendByte(O, true);

  delay(4000);
}
