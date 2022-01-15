#include <ArduinoUnitTests.h>
#include <Arduino.h>
#include <desklab.h>

unittest(test_measurement_method_read_implementation) {
    GodmodeState* state = GODMODE();   
    state->resetPins();        

    state->analogPin[0] = 200; 
    assertEqual(analogRead(0), PhotometerSensorAuslesen(0));
    assertEqual(analogRead(0), photometerReadRaw(0));

    state->analogPin[0] = 500; 
    assertEqual(analogRead(0), PhotometerSensorAuslesen(0));
    assertEqual(analogRead(0), photometerReadRaw(0));

    state->analogPin[0] = 800; 
    assertEqual(analogRead(0), PhotometerSensorAuslesen(0));
    assertEqual(analogRead(0), photometerReadRaw(0));
}

unittest(test_measurement_method_pin_implementation) {
    GodmodeState* state = GODMODE();   
    state->resetPins();        

    state->analogPin[0] = 300;
    state->analogPin[1] = 300; 
    state->analogPin[2] = 300; 
    assertEqual(analogRead(0), PhotometerSensorAuslesen(0));
    assertEqual(analogRead(1), PhotometerSensorAuslesen(1));
    assertEqual(analogRead(2), PhotometerSensorAuslesen(2));
    assertEqual(analogRead(0), photometerReadRaw(0));
    assertEqual(analogRead(1), photometerReadRaw(1));
    assertEqual(analogRead(2), photometerReadRaw(2));

    state->analogPin[0] = 600;
    state->analogPin[1] = 600; 
    state->analogPin[2] = 600; 
    assertEqual(analogRead(0), PhotometerSensorAuslesen(0));
    assertEqual(analogRead(1), PhotometerSensorAuslesen(1));
    assertEqual(analogRead(2), PhotometerSensorAuslesen(2));
    assertEqual(analogRead(0), photometerReadRaw(0));
    assertEqual(analogRead(1), photometerReadRaw(1));
    assertEqual(analogRead(2), photometerReadRaw(2));
}

unittest(test_measurement_method_stackability) {
    GodmodeState* state = GODMODE();   
    state->resetPins();        

    state->analogPin[0] = 200; 
    assertEqual(PhotometerMessung(0), PhotometerBerechnung(PhotometerSensorAuslesen(0)));
    assertEqual(photometerMeasureOD(0), photometerConversion(photometerReadRaw(0)));

    state->analogPin[0] = 500; 
    assertEqual(PhotometerMessung(0), PhotometerBerechnung(PhotometerSensorAuslesen(0)));
    assertEqual(photometerMeasureOD(0), photometerConversion(photometerReadRaw(0)));

    state->analogPin[0] = 800; 
    assertEqual(PhotometerMessung(0), PhotometerBerechnung(PhotometerSensorAuslesen(0)));
    assertEqual(photometerMeasureOD(0), photometerConversion(photometerReadRaw(0)));
}

unittest(test_measurement_method_comparability) {
    GodmodeState* state = GODMODE();   
    state->resetPins();        

    state->analogPin[0] = 200; 
    assertEqual(PhotometerMessung(0), PhotometerBerechnung(200));
    assertEqual(photometerMeasureOD(0), photometerConversion(200));

    state->analogPin[0] = 500; 
    assertEqual(PhotometerMessung(0), PhotometerBerechnung(500));
    assertEqual(photometerMeasureOD(0), photometerConversion(500));

    state->analogPin[0] = 800; 
    assertEqual(PhotometerMessung(0), PhotometerBerechnung(800));
    assertEqual(photometerMeasureOD(0), photometerConversion(800));
}


unittest_main()