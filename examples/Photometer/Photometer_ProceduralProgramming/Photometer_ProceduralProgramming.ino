// This example is part of the desklab-arduino-library implementing methods 
// for the use of desklab (www.desk-lab.de) devices. 
//
// See https://github.com/desklab/desklab-arduino-lib for more information.
//
// License: MIT, Copyright: 2018-2021 desklab gUG (haftungsbeschränkt)


// [EN] Include the desklab library.
// [DE] Einbinden der desklab Bibliothek.
#include <desklab.h>

// [EN] Initialise a variable to save the Pin, 
// to which the Sensor is attached.
// [DE] Initialisieren einer Variable zur Speicherung
// des Pins, an dem der Sensor angeschlossen ist.
int SensorPin = A0;

void setup() { 
    // [EN] Start the display.
    // [DE] Starten des Displays.     
    photometerSetupDisplay();     
}

void loop() {
    // [EN] Measure the OD.         
    // [DE] Messung der OD.
    double OD = photometerMeasureOD(SensorPin);
  
    // [EN] Print the OD to the display.
    // [DE] Ausgabe der OD auf dem Display.
    photometerPrintOD(OD);
  
    // [EN] Wait for 200ms.
    // [DE] Warten für 200ms.
    delay(200);
} 