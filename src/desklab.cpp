/* This file is part of the desklab-arduino-library implementing methods 
 * for the use of desklab (www.desk-lab.de) devices. It is availabe via 
 * the Arduino Library Manager.
 *
 * See https://github.com/desklab/desklab-arduino-lib for more information.
 *
 * Copyright 2018-2021 desklab gUG (haftungsbeschränkt) <orga@desk-lab.de>
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

core::core(){
  this->_serialoutput = false;
  this->_displayoutput = true;
}

void core::enableDisplayOutput(){
  _displayoutput = true;
}

void core::disableDisplayOutput(){
  _displayoutput = false;
}

void core::enableSerialOutput(){
  _serialoutput = true;
}

void core::disableSerialOutput(){
  _serialoutput = false;
}  

void core::print(bool data){
  // TODO:
}

void core::print(int data){
  // TODO:
}

void core::print(double data){
  // TODO:
}

void core::print(float data){
  // TODO:
}

void core::print(char data){
  // TODO:
}

void core::print(String data){
  // TODO:
}

#ifndef ARDUINO_CI_UNITTEST_ACTIVE
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

  oleddisplay.println("Hinweis: ");
  oleddisplay.println("Mikrocontroller und");
  oleddisplay.println("Display erfolgreich");
  oleddisplay.println("gestartet!");
  oleddisplay.display();

  delay(2000);

  oleddisplay.clearDisplay();
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

#endif