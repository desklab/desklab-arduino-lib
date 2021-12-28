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

#ifndef desklab
#define desklab

// VERSION INFORMATION
#define DESKLAB_LIBRARY_VERSION_MAJOR 1
#define DESKLAB_LIBRARY_VERSION_MINOR 2
#define DESKLAB_LIBRARY_VERSION_PATCH 0

#include <ssd1306.h> 

class core {
    public:
        core();

        void enableDisplayOutput();
        void disableDisplayOutput();
        void enableSerialOutput();
        void disableSerialOutput(); 

        #ifndef ARDUINO_CI_UNITTEST_ACTIVE
        void print(bool data);
        void print(int data);
        void print(double data);
        void print(float data);
        void print(char data);
        #endif

    private:
        bool _serialoutput;
        bool _displayoutput;
};


#include  <desklab_photometer.h>


#endif
