// Einbinden der desklab Bibliothek.
#include <desklab.h>

// Initialisieren einer Variable zur Speicherung
// des Pins, an dem der Sensor angeschlossen ist.
int SensorPin = A0;

void setup() {
    // Starten des Displays.
    photometerSetupDisplay();
}

void loop() {
    // Messung der OD.
    double OD = photometerMeasureOD(SensorPin);
  
    // Ausgabe der OD auf dem Display.
    photometerPrintOD(OD);
  
    // Warten für 200ms.
    delay(200);
}