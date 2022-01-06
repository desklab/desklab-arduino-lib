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

#ifndef DLH_PHOTOMETER
#define DLH_PHOTOMETER

#include <desklab.h>

const double PHOTOMETER_CALIBRATION_DEFAULT_PARAM_A = 1.42909711;
const double PHOTOMETER_CALIBRATION_DEFAULT_PARAM_B = -0.00258627252;
const double PHOTOMETER_CALIBRATION_DEFAULT_PARAM_C = 1.12076970/1000000;
const double PHOTOMETER_CALIBRATION_UPPER_LIMIT = 1.2;
const double PHOTOMETER_CALIBRATION_LOWER_LIMIT = -0.05;
const int PHOTOMETER_CALIBRATION_ZERO_CUTOFF = 925;

void photometerSetupDisplay();
void photometerSetupSerial();

void photometerPrintOD(double od);

double photometerReadRaw(int Pin);
double photometerConversion(double analogSensorValue);
double photometerConversion(double analogSensorValue, double calibration_param_A, double calibration_param_B, double calibration_param_C);
double photometerMeasureOD(int Pin);

class Photometer {
    public:
        Photometer(int pin);
        ~Photometer();
        
        void begin();
        void end();

        void setCalibration(double calibration_param_A, double calibration_param_B, double calibration_param_C);

        void enableDisplayOutput();
        void disableDisplayOutput();
        void enableSerialOutput();
        void disableSerialOutput();    

        void measureOD();
        void readSensor();
        void convertSensorvalueToOD();

        double getSensorvalue();
        double getOD();

        void printOD();

    private:
        int _pin;
        bool _serialoutput;
        bool _displayoutput;
        double _calibration_A;
        double _calibration_B;
        double _calibration_C;
        double _sensorvalue;
        double _od;
};



// DEPRECATED METHOD ALIASES
#define PhotometerSensorAuslesen photometerReadRaw
#define PhotometerBerechnung photometerConversion
#define PhotometerMessung photometerMeasureOD

#ifndef ARDUINO_CI_UNITTEST_ACTIVE
#define PhotometerAusgabe photometerPrint
#endif
// END OF DEPRECATED METHOD ALIASES

#endif