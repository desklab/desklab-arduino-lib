#include <ArduinoUnitTests.h>
#include <Arduino.h>
#include <desklab.h>

unittest(test_com_decoding_byte8_to_char) {
    byte8_t byteA = {8,{true,false,false,false,false,false,true,false}}; // A:1000001 CHECK:0
    char A = decode(byteA);
    assertEqual('A',A);

    byte8_t byteD = {8,{true,false,false,false,true,false,false,false}}; // D:1000100 CHECK:0
    char D = decode(byteD);
    assertEqual('D',D);

    byte8_t byteF = {8,{true,false,false,false,true,true,false,true}};   // F:1000110 CHECK:1
    char F = decode(byteF);
    assertEqual('F',F);

    byte8_t byteK = {8,{true,false,false,true,false,true,true,false}};   // K:1001011 CHECK:0
    char K = decode(byteK);
    assertEqual('K',K);

    byte8_t byteX = {8,{true,false,true,true,false,false,false,true}};   // X:1011000 CHECK:1
    char X = decode(byteX);
    assertEqual('X',X);
}



unittest_main()