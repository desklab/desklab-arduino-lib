/*
 * Photometer Detailed
 * ===================
 *
 * Beispiel für die Nutzung der desklab Photometer Bibliothek.
 * Mehr Informationen: https://desk-lab.de/docs
 *
 * Zur Verfügung gestellt durch die desklab gUG (haftungsbeschränkt)
*/

// Einbinden einer Bibliothek mit Funktionen
// für das Photometer von desklab
#include <desklab.h>

// Initialisierung einer Variable vom 
// Typ "double" (Gleitkommazahl) zum
// Speichern des kumulierten SensorWert
double SensorWert_kumuliert;

// Initialisierung einer Variable vom
// Typ "double" (Gleitkommazahl) zum
// Speichern des gemittelten SensorWert
double SensorWert_gemittelt;

// Initialisierung einer Variable vom
// Typ "double" (Gleitkommazahl) zum
// Speichern der optischen Dichte
double OptischeDichte;

void setup()   {      
  // Beginn der Setup-Funktion
  // (wird einmal beim Start ausgeführt)

  // Starte das Display (Anzeige: "Starte Messung!")
  StarteDisplay();    
  
} // Ende der Setup-Funktion


void loop() {         
  // Beginn der Loop-Funktion 
  // (wird nach der Setup-Funktion dauerhaft wiederholt)

  for (int i = 1; i<51; i++) {
    // Schleife wird 50x ausgeführt
    // Summe von 50 Sensorwerten
    SensorWert_kumuliert = SensorWert_kumuliert + (analogRead(A0));
    delay(5);
  }

  // Berechnung des Mittelwerts
  SensorWert_gemittelt = SensorWert_kumuliert / 50;
  // Zurücksetzen der Variable
  SensorWert_kumuliert = 0;

  // Berechnet aus dem Sensorwert die optische Dichte
  OptischeDichte = PhotometerBerechnung(SensorWert_gemittelt);

  // Ausgabe des aktuell in der Variable 
  // "OptischeDichte" gespeicherten Werts auf dem Display
  PhotometerAusgabe(OptischeDichte);

  // Warte für 100 Millisekunden
  delay(100);

} // Ende der Loop-Funktion
