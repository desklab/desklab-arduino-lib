#include <desklab.h>

const int clockPin = 3;
const int dataPin = 4;

void setup() {
    setupReadConnection(dataPin, clockPin);
}

void loop() {
    if(availableByte()){
        byte8_t bitsequence;
        bitsequence = readByte();
        if(check(byte)){
            char output = decode(bitsequence);
            display(output);
            delay(1000);
            clearDisplay();
        } else {
            display('?');
            delay(1000);
            clearDisplay();
        }
    }
}
