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

int dispX = 0;
int dispY = 0;

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
        SSD1306_MODE_t mode = SSD1306_OVERRIDE;
        SSD1306_COLOR_t col = SSD1306_WHITE;
        SSD1306_WRITE_CHAR(dispX, dispY, c, 2, col, mode);
        dispX = dispX + 10;
        SSD1306_DISPLAY_UPDATE();
    }
}

void display(byte8_t b){
    SSD1306_MODE_t mode = SSD1306_OVERRIDE;
    SSD1306_COLOR_t col = SSD1306_WHITE;
    for (int i = 0; i<b.l; i++){
        if (b.bits[i]){
            SSD1306_WRITE_CHAR(dispX + i*10, dispY, '1', 2, col, mode);
        } else {
            SSD1306_WRITE_CHAR(dispX + i*10, dispY, '0', 2, col, mode);
        }
    }
    dispX = dispX + 70;
    SSD1306_DISPLAY_UPDATE();
}


void display(const char* s){
    SSD1306_MODE_t mode = SSD1306_OVERRIDE;
    SSD1306_COLOR_t col = SSD1306_WHITE;;
    SSD1306_WRITE_STRING(dispX, dispY, s, 2, col, mode);
    dispX = dispX + 10*strlen(s);
    SSD1306_DISPLAY_UPDATE(); 
}

void clearDisplay(){
    dispX = 0;
    dispY = 0;
    SSD1306_BUFFER_CLEAR();
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
    sendStartCode();
    for (int i = 0; i<send.l; i++)
    {
        sendBit(send.bits[i]);
    }
    sendEndCode();
    delay(tb);
}

#ifndef ARDUINO_CI_UNITTEST_ACTIVE

void sendByte(byte8_t send, bool print) {
    SSD1306_MODE_t mode = SSD1306_OVERRIDE;
    SSD1306_COLOR_t col = SSD1306_WHITE;
    if(print){
        Serial.print("sending data: "); 
    }
    
    sendStartCode();
    for (int i = 0; i<send.l; i++)
    {
        if(print){
            if (send.bits[i]){
                Serial.print("1");
                SSD1306_WRITE_CHAR(dispX+i*10, 0, '1', 2, col, mode);
                SSD1306_DISPLAY_UPDATE(); 
            } else {
                Serial.print("0");
                SSD1306_WRITE_CHAR(dispX+i*10, 0, '0', 2, col, mode);
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

void sendByte(byte8_t send, bool print, int error) {
    SSD1306_MODE_t mode = SSD1306_OVERRIDE;
    SSD1306_COLOR_t col = SSD1306_WHITE;
    if(print){
        Serial.print("sending data: "); 
    }
    
    sendStartCode();
    for (int i = 0; i<send.l; i++)
    {
        if(print){
            if (send.bits[i]){
                Serial.print("1");
                SSD1306_WRITE_CHAR(dispX+i*10, 0, '1', 2, col, mode);
                SSD1306_DISPLAY_UPDATE(); 
            } else {
                Serial.print("0");
                SSD1306_WRITE_CHAR(dispX+i*10, 0, '0', 2, col, mode);
                SSD1306_DISPLAY_UPDATE(); 
            }
        }
        int r = random(100);
        Serial.println(r);
        Serial.println(error);
        if(r>error){
            sendBit(send.bits[i]);
        } else {
            sendBit(!send.bits[i]);
        }
    }
    sendEndCode();
    if(print){
        Serial.println("");   
    }
    delay(tb);
}

#endif


#ifndef ARDUINO_CI_UNITTEST_ACTIVE
bool check(byte8_t b, bool debug){
    if(debug){
        Serial.println("DEBUG: check(byte8_t)");
        bool check = false;
        uint8_t highBits = 0;

        for(uint8_t i = 0; i < b.l; i++){
            if(b.bits[i]){
                highBits++;            
            }
        }

        Serial.print("number of high bits: ");
        Serial.println(highBits);

        if((highBits % 2) == 0){
            check = true;
            Serial.println("parity check: TRUE");
        } else {
            Serial.println("parity check: FALSE");
        }

        return check;
    } else {
        return check(b);
    }
    
}

char decode(byte8_t b, bool debug){
    if(debug){
        Serial.println("DEBUG: decode(byte8_t)");
        int i = 0;

        Serial.print("bit sequence to decode: ");
        
        for (int k=0; k < 7; k++){
            if(b.bits[k]){
                Serial.print("1");
            } else {
                Serial.print("0");
            }
            if (b.bits[6-k]){
                i = i + round(pow(2,k));
            }   
        }

        char c = i;

        Serial.println("");
        Serial.print("converted to integer: ");
        Serial.println(i);
        Serial.print("decoded to char: ");
        Serial.println(c);
        
        return c;
    } else {
        return decode(b);
    }
}

byte8_t encode(char c, bool debug){
    if(debug){
        Serial.println("DEBUG: encode(char)");
        byte8_t b = {8,{false,false,false,false,false,false,false,false}};
        int i = c;

        Serial.print("char to decode: ");
        Serial.println(c);
        Serial.print("converted to integer: ");
        Serial.println(i);

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

        Serial.print("encoded to bit sequence: ");
        for (int i = 0; i<7; i++) {
            if (send.bits[i]){
                Serial.print("1");
            } else {
                Serial.print("0");
            }
        }
        Serial.println("");

    } else {
        return encode(c);
    }
}

byte8_t parity(byte8_t b, bool debug){
    if(debug){
        Serial.println("DEBUG: parity(byte8_t)");
        uint8_t highBits = 0;

        for(uint8_t i = 0; i < (b.l-1); i++){
            if(b.bits[i]){
                highBits++;            
            }
        }

        Serial.print("number of high bits: ");
        Serial.println(highBits);

        if((highBits % 2) == 0){
            b.bits[b.l-1] = false;
            Serial.println("set parity bit to FALSE");
        } else {
            b.bits[b.l-1] = true;
            Serial.println("set parity bit to TRUE");
        }

        return b;
    } else {
        return parity(b);
    }

}

#endif