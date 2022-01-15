/* This file is part of the desklab-arduino-library implementing methods 
 * for the use of desklab (www.desk-lab.de) devices. It is availabe via 
 * the Arduino Library Manager.
 *
 * See https://github.com/desklab/desklab-arduino-lib for more information.
 *
 * Copyright 2018-2022 desklab gUG (haftungsbeschränkt) <orga@desk-lab.de>
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

#ifndef ARDUINO_CI_UNITTEST_ACTIVE

void setupDisplay(){
  SSD1306_INIT();
}

void setupSerial(){
  Serial.begin(9600);
}

void unsetDisplay(){
}

void unsetSerial(){
  Serial.end();
}

#endif

Core::Core(){
  this->_serialoutput = false;
  this->_displayoutput = true;
}

Core::~Core(){
}

void Core::begin(){
  #ifndef ARDUINO_CI_UNITTEST_ACTIVE
  setupDisplay();
  setupSerial();
  #endif
}

void Core::end(){
  #ifndef ARDUINO_CI_UNITTEST_ACTIVE
  unsetDisplay();
  unsetSerial();
  #endif
}

void Core::enableDisplayOutput(){
  _displayoutput = true;
}

void Core::disableDisplayOutput(){
  _displayoutput = false;
}

void Core::enableSerialOutput(){
  _serialoutput = true;
}

void Core::disableSerialOutput(){
  _serialoutput = false;
}  

#ifndef ARDUINO_CI_UNITTEST_ACTIVE

void Core::print(bool b){
  SSD1306_MODE_t mode = SSD1306_OVERRIDE;
  SSD1306_COLOR_t col = SSD1306_WHITE;
  SSD1306_BUFFER_CLEAR();
  SSD1306_WRITE_BOOL(0, 0, b, 1, col, mode);
  SSD1306_DISPLAY_UPDATE();
}

void Core::print(int i){
  SSD1306_MODE_t mode = SSD1306_OVERRIDE;
  SSD1306_COLOR_t col = SSD1306_WHITE;;
  SSD1306_BUFFER_CLEAR();
  SSD1306_WRITE_INT(0, 0, i, 1, col, mode);
  SSD1306_DISPLAY_UPDATE();
}

void Core::print(double d){
  SSD1306_MODE_t mode = SSD1306_OVERRIDE;
  SSD1306_COLOR_t col = SSD1306_WHITE;;
  SSD1306_BUFFER_CLEAR();
  SSD1306_WRITE_DOUBLE(0, 0, d, 1, col, mode);
  SSD1306_DISPLAY_UPDATE();
}

void Core::print(char c){
  SSD1306_MODE_t mode = SSD1306_OVERRIDE;
  SSD1306_COLOR_t col = SSD1306_WHITE;;
  SSD1306_BUFFER_CLEAR();
  SSD1306_WRITE_CHAR(0, 0, c, 1, col, mode);
  SSD1306_DISPLAY_UPDATE();
}

#endif