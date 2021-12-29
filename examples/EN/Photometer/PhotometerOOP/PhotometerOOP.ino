// Include the desklab library.
#include <desklab.h>

// Initialise a variable to save the Pin, 
// to which the Sensor is attached.
int SensorPin = A0;

// Initialise the object 'Photometer' from the 
// class 'photometer' (defined in the desklab library)
desklab::Photometer Photometer(SensorPin);

void setup() {
    // Initialise the display/the serial connection
    Photometer.begin();
}

void loop() {
    // Measure the OD
    Photometer.measureOD();

    // Update the Display with the last measured OD
    Photometer.printOD();

    // Wait for 200ms.
    delay(200);
}