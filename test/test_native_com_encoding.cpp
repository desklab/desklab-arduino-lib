#include <ArduinoUnitTests.h>
#include <Arduino.h>
#include <desklab.h>

unittest(test_com_encoding_char_to_byte8) {
    byte8_t byteA = {8,{true,false,false,false,false,false,true,false}}; // A:1000001 CHECK:0
    byte8_t A = encode('A');
    byte8_t AA = parity(A);
    for(int i = 0; i<8; i++){
        assertEqual(AA.bits[i],byteA.bits[i]);
    }

    byte8_t byteD = {8,{true,false,false,false,true,false,false,false}}; // D:1000100 CHECK:0
    byte8_t D = encode('D');
    byte8_t DD = parity(D);
    for(int i = 0; i<8; i++){
        assertEqual(DD.bits[i],byteD.bits[i]);
    }

    byte8_t byteF = {8,{true,false,false,false,true,true,false,true}};   // F:1000110 CHECK:1
    byte8_t F = encode('F');
    byte8_t FF = parity(F);
    for(int i = 0; i<8; i++){
        assertEqual(FF.bits[i],byteF.bits[i]);
    }

    byte8_t byteK = {8,{true,false,false,true,false,true,true,false}};   // K:1001011 CHECK:0
    byte8_t K = encode('K');
    byte8_t KK = parity(K);
    for(int i = 0; i<8; i++){
        assertEqual(KK.bits[i],byteK.bits[i]);
    }

    byte8_t byteX = {8,{true,false,true,true,false,false,false,true}};   // X:1011000 CHECK:1
    byte8_t X = encode('X');
    byte8_t XX = parity(X);
    for(int i = 0; i<8; i++){
        assertEqual(XX.bits[i],byteX.bits[i]);
    }
}

unittest_main()