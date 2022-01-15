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

#ifndef DLH_COMMUNICATION
#define DLH_COMMUNICATION

typedef struct {
    uint8_t l;
    bool bits[8];
}byte8_t;

#ifndef ARDUINO_CI_UNITTEST_ACTIVE
void setupINConnection(int dataPin, int clockPin);
void setupOUTConnection(int dataPin, int clockPin);
#endif

void read();
bool availableByte();
byte8_t readByte();
bool check(byte8_t b);
char decode(byte8_t b);

#ifndef ARDUINO_CI_UNITTEST_ACTIVE
bool check(byte8_t b, bool debug);
char decode(byte8_t b, bool debug);
byte8_t encode(char c, bool debug);
byte8_t parity(byte8_t b, bool debug);
#endif

#ifndef ARDUINO_CI_UNITTEST_ACTIVE
void clearDisplay();
void display(char c);
void display(const char* s);
void display(byte8_t b);
void display(bool b);
void sendByte(byte8_t send, bool print);
void sendByte(byte8_t send, bool print, int error);
#endif

void sendHighDataBit();
void sendLowDataBit();
void sendHighCodeBit();
void sendLowCodeBit();
void sendBit(bool bit);
void sendStartCode();
void sendEndCode();
void sendByte(byte8_t send);
byte8_t encode(char c);
byte8_t parity(byte8_t b);


#endif