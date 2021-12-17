# 1 "so.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.35/packs/Microchip/PIC18Fxxxx_DFP/1.2.26/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "so.c" 2
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
# 2 "so.c" 2

void soInit(void) {
 pinMode(PIN_D7, 0);
 pinMode(PIN_B0, 0);
 pinMode(PIN_D6, 0);
}

void PulseEnClock(void){
 digitalWrite(PIN_D7, 1);
 digitalWrite(PIN_D7, 0);
}

void PulseClockData(void){
 digitalWrite(PIN_B0, 1);
 digitalWrite(PIN_B0, 0);
}
void soWrite(int value) {
 char i;
 digitalWrite(PIN_B0, 0);
 for (i = 0; i < 8; i++) {
  digitalWrite(PIN_D6, value & 0x80);
  PulseClockData();
  value <<= 1;
 }
 PulseEnClock();
}
