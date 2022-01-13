#include <desklab.h>

const int clockPin = 3;
const int dataPin = 4;

void setup() {
    setupINConnection(dataPin, clockPin);
}

void loop() {
    if(availableByte()){
        // Programmcode zum Verarbeiten des 
        // empfangenen Bytes hier ergänzen 
    }
}
