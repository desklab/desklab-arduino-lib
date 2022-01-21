#include <desklab.h>

const int clockPin = 3;
const int dataPin = 4;

void setup() {
    setupReadConnection(dataPin, clockPin);
}

void loop() {
    if(availableByte()){
        // Ergänze deinen Programmcode zum Verarbeiten des 
        // empfangenen Bytes hier. Du solltest darauf achten,
        // dass er möglichst schnell ausgeführt werden kann.
        // Verwende daher wenn möglich keine Aufrufe der 
        // delay() - Funktion, da sonst Fehler beim Empfangen
        // des Bytes auftreten können.
    }
}
