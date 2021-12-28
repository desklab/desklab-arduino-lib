// This example is part of the desklab-arduino-library implementing methods 
// for the use of desklab (www.desk-lab.de) devices. 
//
// See https://github.com/desklab/desklab-arduino-lib for more information.
//
// License: MIT, Copyright: 2018-2021 desklab gUG (haftungsbeschränkt)

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