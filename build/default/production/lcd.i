# 1 "lcd.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.35/packs/Microchip/PIC18Fxxxx_DFP/1.2.26/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "lcd.c" 2
# 1 "./so.h" 1



 void soInit (void);
 void soWrite(int value);
# 2 "lcd.c" 2
# 1 "./io.h" 1
# 12 "./io.h"
enum pin_label{
    PIN_A0,PIN_A1,PIN_A2,PIN_A3,PIN_A4,PIN_A5,PIN_A6,PIN_A7,
    PIN_B0,PIN_B1,PIN_B2,PIN_B3,PIN_B4,PIN_B5,PIN_B6,PIN_B7,
    PIN_C0,PIN_C1,PIN_C2,PIN_C3,PIN_C4,PIN_C5,PIN_C6,PIN_C7,
    PIN_D0,PIN_D1,PIN_D2,PIN_D3,PIN_D4,PIN_D5,PIN_D6,PIN_D7,
    PIN_E0,PIN_E1,PIN_E2,PIN_E3,PIN_E4,PIN_E5,PIN_E6,PIN_E7
};
# 43 "./io.h"
void digitalWrite(int pin, int value);
int digitalRead(int pin);
void pinMode(int pin, int type);
# 3 "lcd.c" 2
# 1 "./lcd.h" 1


  void lcdCommand(char value);
  void lcdChar(char value);
  void lcdString(char msg[]);
  void lcdNumber(int value);
  void lcdPosition(int line, int col);
  void lcdInit(void);
# 4 "lcd.c" 2

void delayMicro(int a) {
 volatile int i;


}
void delayMili(int a) {
 volatile int i;
 for (i = 0; i < a; i++) {


 }
}

void pulseEnablePin() {
 digitalWrite(PIN_D4, 1);
 delayMicro(5);
 digitalWrite(PIN_D4, 0);
 delayMicro(5);
}

void pushNibble(char value, int rs) {
 soWrite(value);
 digitalWrite(PIN_D5, rs);
 pulseEnablePin();
}

void pushByte(char value, int rs) {
 soWrite(value >> 4);
 digitalWrite(PIN_D5, rs);
 pulseEnablePin();

 soWrite(value & 0x0F);
 digitalWrite(PIN_D5, rs);
 pulseEnablePin();
}
void lcdCommand(char value) {
 pushByte(value, 0);
 delayMili(2);
}
void lcdPosition(int line, int col) {
 if (line == 0) {
  lcdCommand(0x80 + (col % 16));
 }
 if (line == 1) {
  lcdCommand(0xC0 + (col % 16));
 }
}
void lcdChar(char value) {
 pushByte(value, 1);
 delayMicro(80);
}

void lcdString(char msg[]) {
 int i = 0;
 while (msg[i] != 0) {
  lcdChar(msg[i]);
  i++;
 }
}
void lcdNumber(int value) {
 int i = 1000;
 while (i > 0) {
  lcdChar((value / i) % 10 + 48);
  i /= 10;
 }
}

void lcdInit() {
 pinMode(PIN_D4, 0);
 pinMode(PIN_D5, 0);
 soInit();
 delayMili(15);

 pushNibble(0x03, 0);
 delayMili(5);
 pushNibble(0x03, 0);
 delayMicro(160);
 pushNibble(0x03, 0);
 delayMicro(160);

 pushNibble(0x02, 0);
 delayMili(10);

 lcdCommand(0x28);
 lcdCommand(0x08 + 0x04);
 lcdCommand(0x01);
}
