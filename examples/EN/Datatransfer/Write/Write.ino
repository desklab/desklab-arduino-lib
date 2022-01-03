#include <desklab.h>

int clockPin = 3;
int dataPin = 4;
size_t l = 8;

byte8_t byteA = {l,{true,false,false,false,false,false,true,false}}; // A:1000001 CHECK:0	
byte8_t byteB = {l,{true,false,false,false,false,true,false,false}}; // B:1000010 CHECK:0		
byte8_t byteC = {l,{true,false,false,false,false,true,true,true}};   // C:1000011 CHECK:1
byte8_t byteD = {l,{true,false,false,false,true,false,false,false}}; // D:1000100 CHECK:0
byte8_t byteE = {l,{true,false,false,false,true,false,true,true}};   // E:1000101 CHECK:1	
byte8_t byteF = {l,{true,false,false,false,true,true,false,true}};   // F:1000110 CHECK:1
byte8_t byteG = {l,{true,false,false,false,true,true,true,false}};   // G:1000111 CHECK:0	
byte8_t byteH = {l,{true,false,false,true,false,false,false,false}}; // H:1001000 CHECK:0	
byte8_t byteI = {l,{true,false,false,true,false,false,true,true}};   // I:1001001 CHECK:1	
byte8_t byteJ = {l,{true,false,false,true,false,true,false,true}};   // J:1001010 CHECK:1
byte8_t byteK = {l,{true,false,false,true,false,true,true,false}};   // K:1001011 CHECK:0
byte8_t byteL = {l,{true,false,false,true,true,false,false,true}};   // L:1001100 CHECK:1
byte8_t byteM = {l,{true,false,false,true,true,false,true,false}};   // M:1001101 CHECK:0	
byte8_t byteN = {l,{true,false,false,true,true,true,false,true}};    // N:1001110 CHECK:1
byte8_t byteO = {l,{true,false,false,true,true,true,true,true}};     // O:1001111 CHECK:1
byte8_t byteP = {l,{true,false,true,false,false,false,false,false}}; // P:1010000 CHECK:0
byte8_t byteQ = {l,{true,false,true,false,false,false,true,true}};   // Q:1010001 CHECK:1	
byte8_t byteR = {l,{true,false,true,false,false,true,false,true}};   // R:1010010 CHECK:1
byte8_t byteS = {l,{true,false,true,false,false,true,true,false}};   // S:1010011 CHECK:0	
byte8_t byteT = {l,{true,false,true,false,true,false,false,true}};   // T:1010100 CHECK:1	
byte8_t byteU = {l,{true,false,true,false,true,false,true,false}};   // U:1010101 CHECK:0	
byte8_t byteV = {l,{true,false,true,false,true,true,false,false}};   // V:1010110 CHECK:0	
byte8_t byteW = {l,{true,false,true,false,true,true,true,false}};    // W:1010111 CHECK:1	
byte8_t byteX = {l,{true,false,true,true,false,false,false,true}};   // X:1011000 CHECK:1
byte8_t byteY = {l,{true,false,true,true,false,false,true,false}};   // Y:1011001 CHECK:0	
byte8_t byteZ = {l,{true,false,true,true,false,true,false,false}};   // Z:1011010 CHECK:0	


void setup() {
  setupOUTConnection(dataPin, clockPin);
}


void loop() {        
  sendByte(byteH);
  sendByte(byteE);
  sendByte(byteL);
  sendByte(byteL);
  sendByte(byteO);
  delay(4000);
}
