#include <Arduino.h>
#include <Wire.h>

#include <desklab.h>
#include <ssd1306.h>

//desklab::core Microcontroller;

void setup()   {
    //Microcontroller.enableDisplayOutput();
    SSD1306_DisplayInit();
}

void loop() {         
    //Set cursor
    SSD1306_SetCursor(0,0); 

    delay(2000);

    // Print 
    for (int i = 0; i < 2; i++)
    {
        SSD1306_PrintOSZI(0);
        SSD1306_PrintOSZI(1);
        SSD1306_PrintOSZI(2);
        SSD1306_PrintOSZI(3);
        SSD1306_PrintOSZI(4);
        SSD1306_PrintOSZI(5);
    }
    delay(10000);
    SSD1306_Fill(0x00);
    delay(1000);
} 