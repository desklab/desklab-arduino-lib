#include <Arduino.h>
#include <Wire.h>
#include <ssd1306.h>

SSD1306_t SSD1306 = {
  .MASK_X_LOW = 0,
  .MASK_Y_LOW = 0,
  .MASK_X_HIGH = SSD1306_WIDTH,
  .MASK_Y_HIGH = SSD1306_HEIGHT,
  .INVERTED = 0
};

unsigned char SSD1306_DATA_BUFFER[SSD1306_BUFFER_DATA_MAX];

#ifndef ARDUINO_CI_UNITTEST_ACTIVE

void SSD1306_I2C_WRITE(unsigned char *PACKAGE, uint8_t len) {
  Wire.beginTransmission(SSD1306_ADDR);
  Wire.write(PACKAGE, len);
  Wire.endTransmission();
}

void SSD1306_CMD_WRITE(uint8_t command) {
  unsigned char PACKAGE[2];
  PACKAGE[0] = SSD1306_CONTROL_CMD;
  PACKAGE[1] = command;
  SSD1306_I2C_WRITE(PACKAGE, 2);
}

void SSD1306_CMD_WRITE(uint8_t command, uint8_t data) {
  unsigned char PACKAGE[3];
  PACKAGE[0] = SSD1306_CONTROL_CMD;
  PACKAGE[1] = command;
  PACKAGE[2] = data;
  SSD1306_I2C_WRITE(PACKAGE, 3);
}

void SSD1306_CMD_WRITE(uint8_t command, uint8_t data1, uint8_t data2) {
  unsigned char PACKAGE[4];
  PACKAGE[0] = SSD1306_CONTROL_CMD;
  PACKAGE[1] = command;
  PACKAGE[2] = data1;
  PACKAGE[3] = data2;
  SSD1306_I2C_WRITE(PACKAGE, 4);
}

void SSD1306_I2C_SETUP(){
  delay(10); 
  Wire.begin();
}

void SSD1306_DATA_WRITE() {
  unsigned char PACKAGE[2];
  PACKAGE[0] = SSD1306_CONTROL_DATA;
  for(uint16_t i = 0; i < SSD1306_BUFFER_DATA_MAX; i++) {    
    PACKAGE[1] = SSD1306_DATA_BUFFER[i];
    SSD1306_I2C_WRITE(PACKAGE, 2);
  }
}

void SSD1306_INIT() {
  SSD1306_I2C_SETUP();                         // Establish I2C Connection to Display

  SSD1306_CMD_WRITE(0xAE);                     // Display off
  SSD1306_CMD_WRITE(0xD5, 0x80);               // OSC
  SSD1306_CMD_WRITE(0x81, 0x80);               // Brightness [0~255]
  SSD1306_CMD_WRITE(0x20, 0x00);               // Memory Address Mode [horizontal=0, vertical=1, page(default)=2]
  SSD1306_CMD_WRITE(0xD3, 0x00);               // Display Offset [0~63]
  SSD1306_CMD_WRITE(0x40);                     // Display start line [0x40~0x7F]
  SSD1306_CMD_WRITE(0xA8, SSD1306_HEIGHT-1);   // Multiplex number (activated rows) [height-1, default=63]
  SSD1306_CMD_WRITE(0xDA, 0x02);               // Reduce to half of height (as we use a 32px display)
  SSD1306_CMD_WRITE(0xA1);                     // Segment (Column) Mode [normal=0xA0, inverse=0xA1]
  SSD1306_CMD_WRITE(0xC8);                     // Common (Row) Mode [normal=0xC0, inverse=0xC8]
  SSD1306_CMD_WRITE(0xA6);                     // Display Mode [normal=0xA6, inverse=0xA7]
  SSD1306_CMD_WRITE(0x2E);                     // Disable Scroll
  SSD1306_CMD_WRITE(0x8D, 0x14);               // Charge Pump [On=0x14, Off=0x10]
  SSD1306_CMD_WRITE(0xAF);                     // Display on

  SSD1306_BUFFER_CLEAR();                      // Clear Data Buffer
  SSD1306_DISPLAY_UPDATE(); 

  SSD1306_CMD_WRITE(0x21,0);
  SSD1306_CMD_WRITE(0x22,0,3); 
  SSD1306_DATA_WRITE();                        // Write Data Buffer to SSD1306

  SSD1306_CMD_WRITE(0x21,0,127);
  SSD1306_CMD_WRITE(0x22,4,7);
  SSD1306_DATA_WRITE();                        // Write Data Buffer to SSD1306
}

void SSD1306_DISPLAY_UPDATE() {
  SSD1306_CMD_WRITE(0x21, 0, SSD1306_WIDTH-1);       // Segment (column) start at 0 to 127
  SSD1306_CMD_WRITE(0x22, 0, (SSD1306_HEIGHT/8)-1);  // Page (rows) start at 0 to 3
  SSD1306_DATA_WRITE();                              // Write Data Buffer to SSD1306
}

#endif

uint8_t SSD1306_GET_FONT_HEIGHT(uint8_t s){
  if (s == 1){
    return FONT_7_10_HEIGHT;
  }
  if (s == 2){
    return FONT_11_18_HEIGHT;
  }
  if (s == 3){
    return FONT_16_26_HEIGHT;
  }
  return 0;
}

uint8_t SSD1306_GET_FONT_WIDTH(uint8_t s){
  if (s == 1){
    return FONT_7_10_WIDTH;
  }
  if (s == 2){
    return FONT_11_18_WIDTH;
  }
  if (s == 3){
    return FONT_16_26_WIDTH;
  }
  return 0;
}

void SSD1306_BUFFER_FILL(SSD1306_COLOR_t color) {
  for(uint16_t i = 0; i<SSD1306_BUFFER_DATA_MAX; i++) {
    SSD1306_DATA_BUFFER[i] = color;
  }
}

void SSD1306_BUFFER_CLEAR() {
  SSD1306_BUFFER_FILL(SSD1306_BLACK);
}

void SSD1306_INVERT() {
  SSD1306.INVERTED = !SSD1306.INVERTED;
}

void SSD1306_SET_MASK(int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
  SSD1306.MASK_X_LOW = (x1>=0 && x1<SSD1306_WIDTH) ? x1 : 0;
  SSD1306.MASK_Y_LOW = (y1>=0 && y1<SSD1306_HEIGHT) ? y1 : 0;
  SSD1306.MASK_X_HIGH = (x2>=0 && x2<SSD1306_WIDTH) ? x2 : SSD1306_WIDTH-1;
  SSD1306.MASK_Y_HIGH = (y2>=0 && y2<SSD1306_HEIGHT) ? y2 : SSD1306_HEIGHT-1;
}

void SSD1306_WRITE_PIXEL(int16_t x, int16_t y, SSD1306_COLOR_t color) {
  if (x < SSD1306.MASK_X_LOW ||
      y < SSD1306.MASK_Y_LOW ||
      x >= SSD1306.MASK_X_HIGH ||
      y >= SSD1306.MASK_Y_HIGH) {
    // Error
    return;
  }

  if (SSD1306.INVERTED) {
    color = (SSD1306_COLOR_t)!color;
  }

  if(color == SSD1306_WHITE) {
    SSD1306_DATA_BUFFER[1+ x + (y >> 3) * SSD1306_WIDTH] |= (1 << (y % 8));
  } else {
    SSD1306_DATA_BUFFER[1+ x + (y >> 3) * SSD1306_WIDTH] &= ~(1 << (y % 8));
  }
}

void SSD1306_WRITE_CHAR(int16_t x, int16_t y, char ch, uint8_t s, SSD1306_COLOR_t color, SSD1306_MODE_t mode) {
  uint8_t w = SSD1306_GET_FONT_WIDTH(s);
  uint8_t h = SSD1306_GET_FONT_HEIGHT(s);

  int16_t x0, y0;
  uint16_t b;
  
  // Translate font to screen buffer
  for (y0 = 0; y0 < h; y0++) {

      if (s == 1){
        b = pgm_read_word_near(&Font7x10[0] + ((ch - 32) * h + y0));
      }
      if (s == 2){
        b = pgm_read_word_near(&Font11x18[0] + ((ch - 32) * h + y0));
      }
      if (s == 3){
        b = pgm_read_word_near(&Font16x26[0] + ((ch - 32) * h + y0));
      }

      for (x0 = 0; x0 < w; x0++) {
          if ((b << x0) & 0x8000) {
            SSD1306_WRITE_PIXEL(x + x0, y + y0, (SSD1306_COLOR_t) color);
          }
          else if (mode == SSD1306_OVERRIDE) {
            SSD1306_WRITE_PIXEL(x + x0, y + y0, (SSD1306_COLOR_t)!color);
          }
      }
  }
}

void SSD1306_WRITE_STRING(int16_t x, int16_t y, const char* str, uint8_t s, SSD1306_COLOR_t color, SSD1306_MODE_t mode) {
  uint8_t w = SSD1306_GET_FONT_WIDTH(s);
  uint8_t h = SSD1306_GET_FONT_HEIGHT(s);
  int16_t l = strlen(str);

  if (
      (x + l*w < SSD1306.MASK_X_LOW) ||
      (SSD1306.MASK_X_HIGH < x) ||
      (y + h < SSD1306.MASK_Y_LOW) ||
      (SSD1306.MASK_Y_HIGH < y)
  ){
    return;
  }

  int16_t fx = (SSD1306.MASK_X_LOW - x) / w;
  int16_t rx = (x - SSD1306.MASK_X_HIGH) / h;
  const char* estr = str + l;
  int16_t n = 0;

  // cut off characters which are out of masking box
  if (fx > 0) {
      str += fx;
      x += fx*w;
  }

  if (rx > 0) {
    estr -= rx;
  }

  // write until null-byte or the first cutoff char
  while (*str && str < estr)
  {
      SSD1306_WRITE_CHAR(x + n*w, y, *str, s, color, mode);
      n++;
      str++;
  }
}

void SSD1306_WRITE_DOUBLE(int16_t x, int16_t y, double d, uint8_t s, SSD1306_COLOR_t color, SSD1306_MODE_t mode) {
  uint8_t w = SSD1306_GET_FONT_WIDTH(s);
  //uint8_t h = SSD1306_GET_FONT_HEIGHT(s);

  char buf [4];
  
  #ifndef ARDUINO_CI_UNITTEST_ACTIVE
  dtostrf(d, 0, 2, buf); // TODO: Investigate error in unittests
  #endif

  int n = 0;
  while (n < 4)
  {
      SSD1306_WRITE_CHAR(x + n*w, y, buf[n], s, color, mode);
      n++;
  }

}

void SSD1306_WRITE_INT(int16_t x, int16_t y, int i, uint8_t s, SSD1306_COLOR_t color, SSD1306_MODE_t mode) {
  uint8_t w = SSD1306_GET_FONT_WIDTH(s);
  //uint8_t h = SSD1306_GET_FONT_HEIGHT(s);

  char buf [4]; //TODO: Make size dependent of i
  sprintf (buf, "%03i", i);

  int n = 0;
  while (n < 4) // size dependence needed (see above)
  {
      SSD1306_WRITE_CHAR(x + n*w, y, buf[n], s, color, mode);
      n++;
  }
}

void SSD1306_WRITE_BOOL(int16_t x, int16_t y, bool b, uint8_t s, SSD1306_COLOR_t color, SSD1306_MODE_t mode) {
  //uint8_t w = SSD1306_GET_FONT_WIDTH(s);
  //uint8_t h = SSD1306_GET_FONT_HEIGHT(s);
  char buf;

  if (b){
    buf = 'T';
  } else {
    buf = 'F';
  }

  SSD1306_WRITE_CHAR(x, y, buf, s, color, mode);
}

void SSD1306_WRITE_LINE(int16_t x0, int16_t y0, int16_t x1, int16_t y1, SSD1306_COLOR_t color) {
  int16_t dx, dy, sx, sy, err, e2, i, temp;

  x0 = (x0 >= SSD1306_WIDTH) ? (SSD1306_WIDTH - 1) : x0;
  x1 = (x1 >= SSD1306_WIDTH) ? (SSD1306_WIDTH - 1) : x1;
  y0 = (y0 >= SSD1306_HEIGHT) ? (SSD1306_HEIGHT - 1) : y0;
  y1 = (y1 >= SSD1306_HEIGHT) ? (SSD1306_HEIGHT - 1) : y1;
  
  dx = (x0 < x1) ? (x1 - x0) : (x0 - x1);
  dy = (y0 < y1) ? (y1 - y0) : (y0 - y1);
  sx = (x0 < x1) ? 1 : -1;
  sy = (y0 < y1) ? 1 : -1;
  err = ((dx > dy) ? dx : -dy) / 2;
  
  // Vertical line
  if (dx == 0) {
    if (y1 < y0) {
      temp = y1;
      y1 = y0;
      y0 = temp;
    }

    if (x1 < x0) {
      temp = x1;
      x1 = x0;
      x0 = temp;
    }

    for (i = y0; i <= y1; i++) {
      SSD1306_WRITE_PIXEL(x0, i, color);
    }

    return;
  }

  // Horizontal line
  if (dy == 0) {
    if (y1 < y0) {
      temp = y1;
      y1 = y0;
      y0 = temp;
    }

    if (x1 < x0) {
      temp = x1;
      x1 = x0;
      x0 = temp;
    }

    for (i = x0; i <= x1; i++) {
      SSD1306_WRITE_PIXEL(i, y0, color);
    }

    return;
  }

  while (1) {
    SSD1306_WRITE_PIXEL(x0, y0, color);
    if (x0 == x1 && y0 == y1) {
      break;
    }
    e2 = err;
    if (e2 > -dx) {
      err -= dy;
      x0 += sx;
    }
    if (e2 < dy) {
      err += dx;
      y0 += sy;
    }
  }
}
