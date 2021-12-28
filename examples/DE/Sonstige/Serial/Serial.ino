#include <desklab.h>

desklab::core Microcontroller;

void setup() {
    Microcontroller.enableSerialOutput();
}

void loop() {
    int t = round(millis()/1000);
    Microcontroller.print(t);

    delay(200);
}