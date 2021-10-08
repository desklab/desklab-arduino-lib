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

#include <Arduino.h>
#include <desklab_photometer.h>

void photometerSetupDisplay(){
  // TODO: Setup I2C Connection to display.
}

void photometerPrint(double OD){
  // TODO: Print OD to display.
}

double photometerReadRaw(int Pin){
  double sensorValue = 0;
  double meanSensorValue = 0;

  for (int i = 1; i<51; i++){
    sensorValue = sensorValue + analogRead(Pin);
    delay(5);
  }

  meanSensorValue = sensorValue/50;

  return meanSensorValue;
}

double photometerConversion(double analogSensorValue){
  double opticalDensity = photometerConversion(analogSensorValue, 
    PHOTOMETER_CALIBRATION_DEFAULT_PARAM_A, 
    PHOTOMETER_CALIBRATION_DEFAULT_PARAM_B, 
    PHOTOMETER_CALIBRATION_DEFAULT_PARAM_C);

  return opticalDensity;
}

double photometerConversion(double analogSensorValue, double calibration_param_A, double calibration_param_B, double calibration_param_C){

  double opticalDensity = calibration_param_A + calibration_param_B*analogSensorValue + calibration_param_C*pow(analogSensorValue,2);
  
  if (analogSensorValue > PHOTOMETER_CALIBRATION_ZERO_CUTOFF){
    opticalDensity = opticalDensity-(pow(analogSensorValue-PHOTOMETER_CALIBRATION_ZERO_CUTOFF,2)/80000);
  }
  if ((opticalDensity < 0) & (opticalDensity > -0.01)){
    opticalDensity = 0.00;
  }
  if (opticalDensity < -PHOTOMETER_CALIBRATION_LOWER_LIMIT || opticalDensity > PHOTOMETER_CALIBRATION_UPPER_LIMIT){
    opticalDensity = NAN;
  }

  return opticalDensity;
}

double photometerMeasureOD(int Pin){
  int sensorRaw = photometerReadRaw(Pin);
  double OD = photometerConversion(sensorRaw);
  return OD;
}


photometer::photometer(int pin){
  this->_pin = pin;
  
  this->_serialoutput = false;
  this->_displayoutput = true;

  this->_calibration_A = PHOTOMETER_CALIBRATION_DEFAULT_PARAM_A;
  this->_calibration_B = PHOTOMETER_CALIBRATION_DEFAULT_PARAM_B;
  this->_calibration_C = PHOTOMETER_CALIBRATION_DEFAULT_PARAM_C;

  this->_sensorvalue = NAN;
  this->_od = NAN;

  photometerSetupDisplay();
}

void photometer::measureOD(){
  this->_od = photometerMeasureOD(this->_pin);
}

void photometer::readSensor(){
  this->_sensorvalue = photometerReadRaw(this->_pin);
}

double photometer::getSensorValue(){
  return this->_sensorvalue;
}

double photometer::getOD(){
  return this->_od;
}

void photometer::setCalibration(double calibration_param_A, double calibration_param_B, double calibration_param_C){
  this->_calibration_A = calibration_param_A;
  this->_calibration_B = calibration_param_B;
  this->_calibration_C = calibration_param_C;
}

void photometer::enableDisplayOutput(){
  this->_displayoutput = true;
}

void photometer::disableDisplayOutput(){
  this->_displayoutput = false;
}

void photometer::enableSerialOutput(){
  this->_serialoutput = true;
}

void photometer::disableSerialOutput(){
  this->_serialoutput = false;
}    

void photometer::print(bool data){
  if (this->_displayoutput){
    // TODO: print bool to display
  }

  if (this->_serialoutput)
  {
    // TODO: print bool to serial
  }
}

void photometer::print(int data){
  if (this->_displayoutput){
    // TODO: print int to display
  }

  if (this->_serialoutput)
  {
    // TODO: print int to serial
  }
}

void photometer::print(double data){
  if (this->_displayoutput){
    // TODO: print double to display
  }

  if (this->_serialoutput)
  {
    // TODO: print double to serial
  }
}

void photometer::print(float data){
  if (this->_displayoutput){
    // TODO: print float to display
  }

  if (this->_serialoutput)
  {
    // TODO: print float to serial
  }
}

void photometer::print(char data){
  if (this->_displayoutput){
    // TODO: print char to display
  }

  if (this->_serialoutput)
  {
    // TODO: print char to serial
  }
}