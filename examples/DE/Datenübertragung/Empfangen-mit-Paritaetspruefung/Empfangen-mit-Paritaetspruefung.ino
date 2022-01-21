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
        if(check(bitsequence)){
            char output = decode(bitsequence);
            clearDisplay();
            display(output);
        } else {
            clearDisplay();
            display('?');
        }
    }
}
