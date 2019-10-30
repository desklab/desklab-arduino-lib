/*
 * desklab.cpp
 * ===========
 *
 * Bibliothek zur Nutzung mit dem Experimentier-Set von desklab
 * (www.desk-lab.de).
 *
 * Zur Verfügung gestellt durch die desklab gUG (haftungsbeschränkt)
 *
 * Copyright 2018-2019 desklab gUG <orga@desk-lab.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
*/

#include <desklab.h>
#include <Arduino.h>

double PhotometerSensorAuslesen(int SensorPin){
  double sensorValue = 0;
  double meanSensorValue = 0;

  for (int i = 1; i<51; i++){
    sensorValue = sensorValue+ (analogRead(SensorPin));
    delay(5);
  }
  meanSensorValue = sensorValue/50;

  return meanSensorValue;
}


double PhotometerBerechnung(double sensorValue){
  double opticalDensity = 0;

  opticalDensity = 1.42909711 - 0.00258627252 * sensorValue + 1.12076970 / 1000000 * pow(sensorValue,2);
  if (sensorValue > 925){
    opticalDensity = opticalDensity-(pow(sensorValue-925,2)/80000);
  }
  if ((opticalDensity < 0) & (opticalDensity > -0.01)){
    opticalDensity = 0.00;
  }

  return opticalDensity;
}


double PhotometerMessung(int sensorPin){
  double sensorValue = 0;
  double opticalDensity = 0;

  sensorValue = PhotometerSensorAuslesen(sensorPin);
  opticalDensity = PhotometerBerechnung(sensorValue);

  return opticalDensity;
}


void StarteDisplay(){

  oleddisplay.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  oleddisplay.clearDisplay();

  oleddisplay.drawBitmap(
    (oleddisplay.width()  - LOGO_WIDTH ) / 2,
    (oleddisplay.height() - LOGO_HEIGHT) / 2,
    dl_Logo, LOGO_WIDTH, LOGO_HEIGHT, 1);
  oleddisplay.display();
  delay(1500);

  oleddisplay.clearDisplay();
  oleddisplay.display();

  oleddisplay.setTextColor(WHITE, BLACK);
  oleddisplay.setCursor(0,0);
  oleddisplay.setTextSize(1);

  oleddisplay.println("Arduino und Display");
  oleddisplay.println("erfolgreich gestartet");
  oleddisplay.display();

  delay(2000);

  oleddisplay.clearDisplay();
  oleddisplay.display();
}


void PhotometerAusgabe(double opticalDensity){

  oleddisplay.clearDisplay();
  oleddisplay.setTextSize(1);
  oleddisplay.setCursor(0,0);

  oleddisplay.println("Optische Dichte:");
  oleddisplay.println("");
  oleddisplay.setTextSize(2);
  oleddisplay.print(opticalDensity);
  oleddisplay.display();
}

void TextAusgabe(String printMessage, int printSize){

  oleddisplay.clearDisplay();
  oleddisplay.setTextSize(printSize);
  oleddisplay.setCursor(0,0);

  oleddisplay.println(printMessage);
  oleddisplay.display();
}

void Drehen(int drehen) {
  oleddisplay.setRotation(drehen);
}

Adafruit_SSD1306 Display() {
  return oleddisplay;
}