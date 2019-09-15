/*
 * Photometer Short
 * ================
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

  // Liest den Sensor an A0 aus und berechnet
  // aus dem Sensorwert die optische Dichte
  OptischeDichte = PhotometerMessung(A0);

  // Ausgabe des aktuell in der Variable 
  // "OptischeDichte" gespeicherten Werts auf dem Display
  PhotometerAusgabe(OptischeDichte);

  // Warte für 100 Millisekunden
  delay(100);

} // Ende der Loop-Funktion
