// Include the desklab library.
#include <desklab.h>

// Initialise a variable to save the Pin, 
// to which the Sensor is attached.
int SensorPin = A0;

void setup() {
    // Start the display.
    photometerSetupDisplay();
}

void loop() {
    // Measure the OD.
    double OD = photometerMeasureOD(SensorPin);
  
    // Print the OD to the display.
    photometerPrintOD(OD);
  
    // Wait for 200ms.
    delay(200);
}