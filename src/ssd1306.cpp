#include <Arduino.h>
#include <ssd1306.h>
#include <Wire.h>


int I2C_establish(){
    delay(50); 
    Wire.begin();
    return 0;
}

int I2C_write(unsigned char *buf, unsigned int len)
{
  Wire.beginTransmission(SSD1306_ADDR);
  Wire.write(buf, len);
  Wire.endTransmission();

  return 0;
}
 
void SSD1306_writeData(unsigned char data){
    unsigned char buf[2] = {0};
    int ret;

    buf[0] = 0x40; // Control byte specifying that the following byte contains data
    buf[1] = data;
  
    ret = I2C_write(buf, 2);
}

void SSD1306_writeCommand(unsigned char cmd){
    unsigned char buf[2] = {0};
    int ret;

    buf[0] = 0x00; // Control byte specifying that the following byte contains a command
    buf[1] = cmd;
  
    ret = I2C_write(buf, 2);
}

void SSD1306_SetCursor(uint8_t page, uint8_t segment )
{
  /* Move the Cursor to specified position only if it is in range */
  if((page <= SSD1306_MAX_PAGE) && (segment < SSD1306_MAX_SEG))
  {
    int SSD1306_LineNum   = page;             // Save the specified line number
    int SSD1306_CursorPos = segment;          // Save the specified cursor position

    SSD1306_writeCommand(0x21);              // cmd for the column start and end address
    SSD1306_writeCommand(segment);           // column start addr
    SSD1306_writeCommand(SSD1306_MAX_SEG-1); // column end addr

    SSD1306_writeCommand(0x22);              // cmd for the page start and end address
    SSD1306_writeCommand(page);              // page start addr
    SSD1306_writeCommand(SSD1306_MAX_PAGE);  // page end addr
  }
}

void SSD1306_PrintOSZI(unsigned int c){
  uint8_t data_byte;

  for (uint8_t i = 0; i < SSD1306_FontSize; i++) {  
    data_byte= SSD1306_OSZI_FONT[c][i]; // Get the data to be displayed from LookUptable

    SSD1306_writeData(data_byte);  // write data to the OLED
    //SSD1306_PosSeg++;
    
  }

  SSD1306_writeData(0x00);         // Display the data
  
}

void SSD1306_InvertDisplay(bool invert) {
  if(invert) {
    SSD1306_writeCommand(0xA7); // Invert the display
  } else {
    SSD1306_writeCommand(0xA6); // Normal display
  }
}

void SSD1306_SetBrightness(uint8_t brightnessValue)
{
    SSD1306_writeCommand(0x81);            // SET Contrast 
    SSD1306_writeCommand(brightnessValue); // Contrast value (default value = 0x7F)
}
 
int SSD1306_DisplayInit(void)
{
    // Establish I2C Connection to the SSD_1306 / OLED Display
    I2C_establish();

    // Commands to initialize the SSD_1306 / OLED Display
    SSD1306_writeCommand(0xAE); // Display OFF
    
    SSD1306_writeCommand(0xD5); // SET Display Clock Divide Ratio and Oscillator Frequency
    SSD1306_writeCommand(0x80); // Default Setting for Display Clock Divide Ratio and Oscillator Frequency that is recommended
    
    SSD1306_writeCommand(0xA8); // SET Multiplex Ratio
    SSD1306_writeCommand(0x3F); // 64 COM lines

    SSD1306_writeCommand(0xD3); // SET display offset
    SSD1306_writeCommand(0x00); // 0 offset
    
    SSD1306_writeCommand(0x40); // SET first line as the start line of the display
    SSD1306_writeCommand(0x8D); // Charge pump
    SSD1306_writeCommand(0x14); // Enable charge dump during display on

    SSD1306_writeCommand(0x20); // SET memory addressing mode
    SSD1306_writeCommand(0x00); // Horizontal addressing mode

    //SSD1306_writeCommand(0xA1); // SET segment remap
                                // column address 127 mapped to segment 0

    SSD1306_writeCommand(0xC8); // SET com output scan direction 
                                // scan from com63 to com 0
    
    SSD1306_writeCommand(0xDA); // SET com pins hardware configuration
    SSD1306_writeCommand(0x12); // Alternative com pin configuration, disable com left/right remap
    
    SSD1306_writeCommand(0x81); // SET Contrast control
    SSD1306_writeCommand(0x80); // SET Contrast to 128

    SSD1306_writeCommand(0xD9); // SET pre-charge period
    SSD1306_writeCommand(0xF1); // Phase 1 period of 15 DCLK, Phase 2 period of 1 DCLK

    SSD1306_writeCommand(0xDB); // SET Vcomh deselect level
    SSD1306_writeCommand(0x20); // Vcomh deselect level ~ 0.77 VCC

    SSD1306_writeCommand(0xA4); // Entire display ON, resume to RAM content display

    SSD1306_writeCommand(0xA6); // SET Display to Normal Mode

    SSD1306_writeCommand(0x2E); // Deactivate scroll

    SSD1306_writeCommand(0xAF); // Display ON
    
    
    SSD1306_Fill(0x00); // Clear the display

    return 0;
}
 
void SSD1306_Fill(unsigned char data)
{
  unsigned int total  = 128 * 8;  

  for(unsigned int i = 0; i < total; i++)
  {
      SSD1306_writeData(data);
  }
}
 
// ================================================================
// TEMPORARY FUNCTIONS FOR TESTING TODO: remove before release
// ================================================================

