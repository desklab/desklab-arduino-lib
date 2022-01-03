#include <ArduinoUnitTests.h>
#include <Arduino.h>
#include <desklab.h>

unittest(test_com_add_parity) {
    byte8_t a = {8,{false,false,false,false,false,false,false,false}};
    byte8_t b = parity(a);
    for(int i = 0; i<8; i++){
        assertEqual(a.bits[i],b.bits[i]);
    }

    byte8_t c = {8,{false,true,false,true,false,false,false,false}};
    byte8_t d = parity(c);
    for(int i = 0; i<8; i++){
        assertEqual(c.bits[i],d.bits[i]);
    }

    byte8_t e = {8,{true,true,true,true,true,true,true,true}};
    byte8_t f = parity(e);
    for(int i = 0; i<8; i++){
        assertEqual(c.bits[i],d.bits[i]);
    }
    
    byte8_t g = {8,{false,true,false,true,true,false,false,false}};
    byte8_t h = parity(g);
    byte8_t j = {8,{false,true,false,true,true,false,false,true}};
    for(int i = 0; i<8; i++){
        assertEqual(h.bits[i],j.bits[i]);
    }

    byte8_t k = {8,{true,true,false,true,true,false,false,true}};
    byte8_t l = parity(k);
    byte8_t m = {8,{true,true,false,true,true,false,false,false}};
    for(int i = 0; i<8; i++){
        assertEqual(l.bits[i],m.bits[i]);
    }
}

unittest(test_pm_check_parity_is_true) {
    byte8_t a = {8,{false,false,false,false,false,false,false,false}};
    assertEqual(check(a),true);

    byte8_t b = {8,{true,true,false,true,false,false,false,true}};
    assertEqual(check(b),true);

    byte8_t c = {8,{true,true,false,true,true,false,false,false}};
    assertEqual(check(c),true);

    byte8_t d = {8,{true,false,true,false,false,true,false,true}};
    assertEqual(check(d),true);
}

unittest(test_pm_check_parity_is_false) {
    byte8_t a = {8,{false,false,false,false,false,false,false,true}};
    assertEqual(check(a),false);

    byte8_t b = {8,{true,true,false,true,false,false,false,false}};
    assertEqual(check(b),false);

    byte8_t c = {8,{true,true,false,true,true,false,false,true}};
    assertEqual(check(c),false);

    byte8_t d = {8,{true,false,true,false,false,true,false,false}};
    assertEqual(check(d),false);
}

unittest_main()