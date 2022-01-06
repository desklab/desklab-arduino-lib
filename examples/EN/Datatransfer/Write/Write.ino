#include <desklab.h>

int clockPin = 3;
int dataPin = 4;

void setup() {
  setupOUTConnection(dataPin, clockPin);
}


void loop() {
  byte8_t bH = encode('H');
  byte8_t bHp = parity(bH);    
  sendByte(bHp);

  byte8_t bE = encode('E');
  byte8_t bEp = parity(bE);   
  sendByte(bEp);

  byte8_t bL = encode('L');
  byte8_t bLp = parity(bL); 
  sendByte(bLp);
  sendByte(bLp);

  byte8_t bO = encode('O');
  byte8_t bOp = parity(bO); 
  sendByte(bOp);

  delay(4000);
}
