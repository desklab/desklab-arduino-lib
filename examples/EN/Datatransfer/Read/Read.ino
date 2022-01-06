#include <desklab.h>

const int clockPin = 3;
const int dataPin = 4;

void setup() {
    Serial.begin(9600);
    setupINConnection(dataPin, clockPin);
}

void loop() {
    if(availableByte()){
        byte8_t byte = readByte();
        if(check(byte)){
            char data = decode(byte);
            display(data);
        }
    }
}
