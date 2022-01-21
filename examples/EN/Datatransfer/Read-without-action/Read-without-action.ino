#include <desklab.h>

const int clockPin = 3;
const int dataPin = 4;

void setup() {
    setupReadConnection(dataPin, clockPin);
}

void loop() {
    if(availableByte()){
        // Add your code to process the received byte here.
        // Make sure that its execution time is minimized.
        // Therefore you should avoid calls to delay(), otherwise
        // errors when receiving the byte may occur.
    }
}
