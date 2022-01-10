#include <Arduino.h>
#include <ssd1306.h>
#include <desklab.h>
#include <communication.h>

bool buffer[] = {false, false, false, false, false, false, false, false, 
                 false, false, false, false, false, false, false, false, 
                 false, false, false, false, false, false, false, false, 
                 false, false, false, false, false, false, false, false};

bool startcode[] = {false, true, false, true, true, true, true, true};
bool endcode[] = {false, true, false, true, false, false, false, false};

bool locked = false;
bool processed = false;

int dPin = 0;
int cPin = 0;

#ifndef ARDUINO_CI_UNITTEST_ACTIVE

void setupINConnection(int dataPin, int clockPin){
    attachInterrupt(digitalPinToInterrupt(clockPin), read, RISING);   

    Serial.begin(9600);

    dPin = dataPin;
    cPin = clockPin;

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    setupDisplay();
    delay(100);
}

void setupOUTConnection(int dataPin, int clockPin){
    Serial.begin(9600);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
  
    digitalWrite(clockPin, LOW);
    digitalWrite(dataPin, LOW);

    dPin = dataPin;
    cPin = clockPin;
    
    setupDisplay();
    delay(100);
}

#endif

void read() {
    locked = true;
    for (size_t i = 0; i < 31; i++)
    {
        buffer[i] = buffer[i+1];
    }
    
    buffer[31] = digitalRead(dPin);

    locked = false;
}

bool availableByte(){
    bool flag = true;
    if (!locked) {
        //Serial.print("Buffer: ");
        //for (size_t i = 0; i<32; i++){
        //    if (buffer[i]){
        //        Serial.print("1");
        //    } else {
        //        Serial.print("0");
        //    }
        //}
        //Serial.println("");
        
        for (size_t i = 0; i<8; i++){
            if (buffer[i] != startcode[i]){
                flag = false;
                processed = false;
            }  
        }
        for (size_t i = 0; i<8; i++){
            if (buffer[24+i] != endcode[i]){
                flag = false;
                processed = false;
            }  
        }
    }

    bool available = false;
    if (flag && !processed){
        available = true;
    }

    return available;
}

byte8_t readByte(){
    byte8_t in = {8,{false,false,false,false,false,false,false,false}};
    for (size_t i = 0; i<8; i++) {
        in.bits[i] = buffer[8+(2*i)];
    }
    
    //Serial.print("received data: ");
    //for (size_t i = 0; i<8; i++){
    //    if (in.bits[i]){
    //        Serial.print("1");
    //    } else {
    //        Serial.print("0");
    //    }
    //}
    //Serial.println("");

    processed = true;
    return in;
}

bool check(byte8_t b){
    bool check = false;
    uint8_t highBits = 0;

    for(uint8_t i = 0; i < b.l; i++){
        if(b.bits[i]){
            highBits++;            
        }
    }

    if((highBits % 2) == 0){
        check = true;
    }

    return check;
}

char decode(byte8_t b)
{
    int i = 0;
    
    for (int k=0; k < 7; k++){
        if (b.bits[6-k]){
            i = i + round(pow(2,k));
        }   
    }

    char c = i;
    
    //if(i != 0){
    //    Serial.print("decoded to: ");
    //    Serial.println(c);
    //}

    return c;
}

byte8_t encode(char c){
    byte8_t b = {8,{false,false,false,false,false,false,false,false}};
    int i = c;
    for(int n = 6; n>=0; n--){
        if(i >= round(pow(2,n))){
            int r = i - round(pow(2,n));
            i = r;
            b.bits[6-n] = true;
            if(i == 0){
                return b;
            }
        }
    }
}

byte8_t parity(byte8_t b){
    uint8_t highBits = 0;

    for(uint8_t i = 0; i < (b.l-1); i++){
        if(b.bits[i]){
            highBits++;            
        }
    }

    if((highBits % 2) == 0){
        b.bits[b.l-1] = false;
    } else {
        b.bits[b.l-1] = true;
    }

    return b;
}

#ifndef ARDUINO_CI_UNITTEST_ACTIVE

void display(char c){
    int i = c;
    if(i != 0){
        //Serial.print("Display: ");
        //Serial.println(c);
        SSD1306_MODE_t mode = SSD1306_OVERRIDE;
        SSD1306_COLOR_t col = SSD1306_WHITE;
        SSD1306_BUFFER_CLEAR();
        SSD1306_WRITE_CHAR(0, 0, c, 2, col, mode);
        SSD1306_DISPLAY_UPDATE();
    }
}

void display(byte8_t b){
    SSD1306_MODE_t mode = SSD1306_OVERRIDE;
    SSD1306_COLOR_t col = SSD1306_WHITE;
    SSD1306_BUFFER_CLEAR();  
    for (int i = 0; i<b.l; i++){
        if (b.bits[i]){
            SSD1306_WRITE_CHAR(i*10, 0, '1', 2, col, mode);
        } else {
            SSD1306_WRITE_CHAR(i*10, 0, '0', 2, col, mode);
        }
    }
    SSD1306_DISPLAY_UPDATE();
}

#endif


int tc = 100;        // [ms] one (internal) clock cycle (400->0.1/s, 40-> 1/s, 4->10/s)
int tw = tc/4;       // [ms] wait for data line to get pulled
int tp = tc-(2*tw);  // [ms] duration of clock pulse
int tr = tc-tp;      // [ms] time available for reading
int tb = 20*tc;      // [ms] duration to wait after sending a byte      

void sendHighDataBit() { //send slow 1
  digitalWrite(dPin, HIGH);
  delay(tw);
  digitalWrite(cPin, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(tp);
  digitalWrite(cPin, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  delay(tw);

  digitalWrite(dPin, HIGH);
  delay(tw);
  digitalWrite(cPin, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(tp);
  digitalWrite(cPin, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  delay(tw);
}

void sendLowDataBit() { // send slow 0
  digitalWrite(dPin, LOW);
  delay(tw);
  digitalWrite(cPin, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(tp);
  digitalWrite(cPin, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  delay(tw);

  digitalWrite(dPin, LOW);
  delay(tw);
  digitalWrite(cPin, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(tp);
  digitalWrite(cPin, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  delay(tw);
}

void sendHighCodeBit() { // send fast 1
  digitalWrite(dPin, HIGH);
  delay(tw);
  digitalWrite(cPin, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(tp);
  digitalWrite(cPin, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  delay(tw);
}

void sendLowCodeBit() { // send fast 0
  digitalWrite(dPin, LOW);
  delay(tw);
  digitalWrite(cPin, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(tp);
  digitalWrite(cPin, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  delay(tw);
}

void sendBit(bool bit) {
  if (bit) {
    sendHighDataBit();
  } else {
    sendLowDataBit();
  }
}

void sendStartCode() { // 01011111 [fast]
  sendLowCodeBit();
  sendHighCodeBit();
  sendLowCodeBit();
  sendHighCodeBit();
  sendHighCodeBit();
  sendHighCodeBit();
  sendHighCodeBit();
  sendHighCodeBit();
}

void sendEndCode() { // 0101000 [fast]
  sendLowCodeBit();
  sendHighCodeBit();
  sendLowCodeBit();
  sendHighCodeBit();
  sendLowCodeBit();
  sendLowCodeBit();
  sendLowCodeBit();
  sendLowCodeBit();
}

void sendByte(byte8_t send) {
    //Serial.print("sending data: ");
    sendStartCode();
    for (int i = 0; i<send.l; i++)
    {
        //if (send.bits[i]){
        //    Serial.print("1");
        //} else {
        //    Serial.print("0");
        //}
        sendBit(send.bits[i]);
    }
    sendEndCode();
    //Serial.println("");
    delay(tb);

}

#ifndef ARDUINO_CI_UNITTEST_ACTIVE

void sendByte(byte8_t send, bool print) {
    SSD1306_MODE_t mode = SSD1306_OVERRIDE;
    SSD1306_COLOR_t col = SSD1306_WHITE;
    if(print){
        Serial.print("sending data: ");
        SSD1306_BUFFER_CLEAR();
        SSD1306_WRITE_CHAR(0, 0, decode(send), 2, col, mode);
        SSD1306_WRITE_CHAR(10, 0, ':', 2, col, mode);
        SSD1306_DISPLAY_UPDATE(); 
    }
    
    sendStartCode();
    for (int i = 0; i<send.l; i++)
    {
        if(print){
            if (send.bits[i]){
                Serial.print("1");
                SSD1306_WRITE_CHAR(24+i*10, 0, '1', 2, col, mode);
                SSD1306_DISPLAY_UPDATE(); 
            } else {
                Serial.print("0");
                SSD1306_WRITE_CHAR(24+i*10, 0, '0', 2, col, mode);
                SSD1306_DISPLAY_UPDATE(); 
            }
        }
        sendBit(send.bits[i]);
    }
    sendEndCode();
    if(print){
        Serial.println("");   
    }
    delay(tb);
}

#endif