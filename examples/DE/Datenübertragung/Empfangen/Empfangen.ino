#include <desklab.h>

const int clockPin = 3;
const int dataPin = 4;

void setup() {
    setupINConnection(dataPin, clockPin);
}

void loop() {
    if(availableByte()){
        byte8_t byte;
        byte = readByte();
        if(check(byte)){
            char data = decode(byte);
            display(data);
        }
    }
}
