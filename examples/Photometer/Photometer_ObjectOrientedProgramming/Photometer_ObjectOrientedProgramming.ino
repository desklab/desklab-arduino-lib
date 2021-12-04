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

// [EN] Initialise the object 'Photometer' from the 
// class 'photometer' (defined in the desklab library)
// [DE] Initialisieren des Objekts 'Photometer' aus der
// Klasse 'photometer' (definiert in der desklab Bibliothek)
desklab::photometer Photometer(SensorPin);

void setup() {
}

void loop() {      
    // [EN] Measure the OD
    // [DE] Messung der OD
    Photometer.measureOD();

    // [EN] Update the Display with the last measured OD
    // [DE] Aktualisieren des Displays mit der letzen gemessenen OD
    Photometer.printOD();

    // [EN] Wait for 200ms.
    // [DE] Warten für 200ms.
    delay(200);
} 