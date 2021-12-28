// [DE] Einbinden der desklab Bibliothek.
#include <desklab.h>

// Initialisieren einer Variable zur Speicherung
// des Pins, an dem der Sensor angeschlossen ist.
int SensorPin = A0;

// Initialisieren des Objekts 'Photometer' aus der
// Klasse 'photometer' (definiert in der desklab Bibliothek)
desklab::photometer Photometer(SensorPin);

void setup() {
}

void loop() {
    // Messung der OD
    Photometer.measureOD();

    // Aktualisieren des Displays mit der letzen gemessenen OD
    Photometer.printOD();

    // Warten für 200ms.
    delay(200);
}