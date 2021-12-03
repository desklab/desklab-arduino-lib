#ifndef ssd1306
#define ssd1306

#include <Arduino.h>

#define SSD1306_DEVICE_NAME "OLED"  // OLED Device Name
#define SSD1306_ADDR 0x3C           // OLED I2C Address
#define SSD1306_WIDTH 128           // OLED Width
#define SSED1306_HEIGHT 32          // OLED HEIGHT
#define SSD1306_MAX_SEG 128         // Maximum segment
#define SSD1306_MAX_PAGE 3          // Maximum line
#define SSD1306_DEFAULT_FONT_SIZE 4 // Default font size [px]

int I2C_Write(unsigned char *buf, unsigned int len);
int establishI2C();
int SSD1306_DisplayInit(void);
void SSD1306_PrintOSZI(unsigned int c);
void SSD1306_InvertDisplay(bool need_to_invert);
void SSD1306_SetBrightness(uint8_t brightnessValue);
void SSD1306_Fill(unsigned char data);
void SSD1306_GoToNextLine(void);
void SSD1306_SetCursor(uint8_t lineNo, uint8_t cursorPos);
void SSD1306_Write(bool is_cmd, unsigned char data);


static uint8_t SSD1306_PosPage = 2;
static uint8_t SSD1306_PosSeg = 0;
static uint8_t SSD1306_FontSize = SSD1306_DEFAULT_FONT_SIZE;

/* static const unsigned char SSD1306_OSZI_FONT[][SSD1306_DEFAULT_FONT_SIZE]= 
{
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // none     [0]
    {0x40, 0x40, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80},   // TRUE     [1]
    {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},   // FALSE    [2]
    {0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},   // RISING   [3]
    {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFF},   // FALLING  [4]
}; */

static const unsigned char SSD1306_OSZI_FONT[][SSD1306_DEFAULT_FONT_SIZE]= 
{
    {0x00, 0x00, 0x00, 0x00},  // NONE    [0]
    {0xFF, 0xFF, 0xFF, 0xFF},  // FULL    [1]
    {0xFF, 0x80, 0x80, 0x80},  // FALLING [2]
    {0xFF, 0x02, 0x02, 0x02},  // RISING  [3]
    {0x80, 0x80, 0x80, 0x80},  // HIGH    [4]
    {0x02, 0x02, 0x02, 0x02}   // LOW     [5]
};

/* static const unsigned char SSD1306_OSZI_FONT[][SSD1306_DEFAULT_FONT_SIZE]= 
{
    {0x00},  // none [0]
    {0x80},  // HIGH [1]
    {0x02},  // LOW [2]
    {0xFF}   // CHANGE [3]
}; */

#endif