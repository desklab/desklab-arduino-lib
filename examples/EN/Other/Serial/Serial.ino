#include <desklab.h>

desklab::Core Microcontroller;

void setup() {
    Microcontroller.enableSerialOutput();
    Microcontroller.begin();
}

void loop() {
    int t = round(millis()/1000);
    Microcontroller.print(t);

    delay(200);
}