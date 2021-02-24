#include <ArduinoUnitTests.h>
#include <Arduino.h>
#include <desklab.h>

unittest(test_pm_measurement_low_range_exceedance) {
    assertNAN(PhotometerBerechnung(0));
    assertNAN(PhotometerBerechnung(10));
}

unittest(test_pm_measurement_high_range_exceedance) {
    assertNAN(PhotometerBerechnung(1000));
    assertNAN(PhotometerBerechnung(1023));
}

unittest(test_pm_measurement_in_range_is_not_nan) {
    assertNotNAN(PhotometerBerechnung(200));
    assertNotNAN(PhotometerBerechnung(300));
    assertNotNAN(PhotometerBerechnung(400));
    assertNotNAN(PhotometerBerechnung(500));
    assertNotNAN(PhotometerBerechnung(600));
    assertNotNAN(PhotometerBerechnung(700));
    assertNotNAN(PhotometerBerechnung(800));
}


unittest_main()