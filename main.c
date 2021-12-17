//Author: Thiago B. Araújo
//Matricula: 2021032968                    PAREI NO BOILER, SEGUIR EXEMPLO DA TEMP

#include <proc/pic18f4520.h>
#include "config.h"
#include "bits.h"
#include "delay.h"
#include "lcd.h"
#include "serial.h"
#include "keypad.h"
#include "menu.h"
#include "rgb.h"
#include "ssd.h"
#include "timer.h"
#include "pwm.h"
#include "adc.h"
#include "io.h"

#define L_ON	0x0F
#define L_OFF	0x08
#define L_CLR	0x01
#define L_L1	0x80
#define L_L2	0xC0
#define menuMax 3

//GLOBAIS
char menuNum = 1, subMenu = 1;
unsigned int pres = 15, temp = 250;
unsigned char lev = 80;
char flag;

void InfBoiler(void) {
    char cmd = serialRead();

    if (cmd != 0) {
        switch (cmd) {
            case 'T':
                serialSend('T');
                temp++;
                break;

            case 't':
                serialSend('p');
                if (temp >= 0) {
                    temp--;
                }
                break;

            case 'P':
                serialSend('P');
                pres++;
                break;

            case 'p':
                serialSend('p');
                if (pres >= 0) {
                    pres--;
                }
                break;


            case 'N':
                serialSend('N');
                if (lev >= 0) {
                    lev--;
                }
                break;

            default:
                break;
        }
    }

}

void status(void) {
    if (pres > 20 || temp > 300) { //pressao ou temperatura fora do aceitavel
        //flag = 0;
        digitalWrite(DISP_1_PIN,HIGH);
        ssdDigit(84, 0);
        pwmSet(100);
    } else {
        pwmSet(0);
        //flag = 1;
        PORTD = 0b00000010; //acende verde
    }
}

void vap(void) {
    int v;
    v = 15;

    ssdDigit((v / 10) % 10, 2);
    ssdDigit((v / 1) % 10, 3);
}

void main() {

    TRISD = 0x00;
    char slot = 0;

    lcdInit();
    kpInit();
    serialInit();
    pwmInit();
    timerInit();
    ssdInit();


    pwmSet(0);
    lcdString("Iniciando...");
    tempo(10);

    lcdCommand(L_CLR);

    for (;;) {
        
        digitalWrite(DISP_1_PIN, LOW);
        digitalWrite(DISP_2_PIN, LOW);
        digitalWrite(DISP_3_PIN, LOW);
        digitalWrite(DISP_4_PIN, LOW);
        
        timerReset(6500);
        switch (slot) {
            case 0:
                leituraMenu();
                switch (menuNum) {
                    case 1:
                        menu1(subMenu);
                        menuCtrl(menuNum, subMenu);
                        break;

                    case 2:
                        menu2(subMenu);
                        menuCtrl(menuNum, subMenu);
                        break;

                    case 3:
                        menu3(subMenu);
                        menuCtrl(menuNum, subMenu);
                        break;

                }//end switch2
                slot = 1;
                break;

            case 1:
                kpDebounce();
                slot = 2;
                break;

            case 2:
                InfBoiler();
                slot = 3;
                break;

            case 3:
                status();
                slot = 4;
                break;

            case 4:
                if (flag == 1) {
                    vap();
                }
                slot = 0;
                break;

            default:
                break;

        }
        timerWait();
        //ssdUpdate();
    }//end for
}