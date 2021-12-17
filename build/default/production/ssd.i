# 1 "ssd.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.35/packs/Microchip/PIC18Fxxxx_DFP/1.2.26/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "ssd.c" 2
# 21 "ssd.c"
# 1 "./ssd.h" 1
# 22 "./ssd.h"
 void ssdDigit(char val, char pos);
 void ssdUpdate(void);
 void ssdInit(void);
# 22 "ssd.c" 2
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
# 23 "ssd.c" 2
# 1 "./so.h" 1



 void soInit (void);
 void soWrite(int value);
# 24 "ssd.c" 2




static const char valor[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

static char display;

static char v0, v1, v2, v3;

void ssdDigit(char val, char pos) {
    if (pos == 0) {
        v0 = val;
    }
    if (pos == 1) {
        v1 = val;
    }
    if (pos == 2) {
        v2 = val;
    }
    if (pos == 3) {
        v3 = val;
    }

}

void ssdUpdate(void) {



    digitalWrite(PIN_D0,0);
    digitalWrite(PIN_D1,0);
    digitalWrite(PIN_D2,0);
    digitalWrite(PIN_D3,0);


    soWrite(0x00);

    switch (display)
    {
        case 0:
            soWrite(valor[v0]);
            digitalWrite(PIN_D0,1);
            display = 1;
            break;

        case 1:
            soWrite(valor[v1]);
            digitalWrite(PIN_D1,1);
            display = 2;
            break;

        case 2:
            soWrite(valor[v2]);
            digitalWrite(PIN_D2,1);
            display = 3;
            break;

        case 3:
            soWrite(valor[v3]);
            digitalWrite(PIN_D3,1);
            display = 0;
            break;

        default:
            display = 0;
            break;
    }
}

void ssdInit(void) {

    pinMode(PIN_D0, 0);
    pinMode(PIN_D1, 0);
    pinMode(PIN_D2, 0);
    pinMode(PIN_D3, 0);


    soInit();

}
