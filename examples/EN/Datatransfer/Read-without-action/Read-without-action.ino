#include <desklab.h>

const int clockPin = 3;
const int dataPin = 4;

void setup() {
    setupINConnection(dataPin, clockPin);
}

void loop() {
    if(availableByte()){
        // Add your code to process the received byte here 
    }
}
