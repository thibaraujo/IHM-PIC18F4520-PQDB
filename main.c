//Author: Thiago B. Araújo
//Matricula: 2021032968                    
//UNIFEI, CAMPUS ITAJUBÁ

//BIBLIOTECAS
#include <proc/pic18f4520.h>
#include "config.h"
#include "bits.h"
#include "delay.h"
#include "lcd.h"
#include "serial.h"
#include "keypad.h"
#include "menu.h"
#include "rgb.h"
#include "timer.h"
#include "pwm.h"
#include "io.h"

//MAPEAMENTO LCD
#define L_ON	0x0F
#define L_OFF	0x08
#define L_CLR	0x01
#define L_L1	0x80
#define L_L2	0xC0

//QUANTIDADE DE MENUS
#define menuMax 3

//GLOBAIS
char menuNum = 1, subMenu = 1;
unsigned int pres = 15, temp = 250;
unsigned char lev = 80;

void InfBoiler(void) {//INFORMACOES ADVINDAS DA CALDEIRA (AUMENTO OU DECRESCIMO DE GRANDEZAS)
    char cmd = serialRead();

    if (cmd != 0) {
        switch (cmd) {
            case 'T':
                serialSend('T');
                temp++;
                break;

            case 't':
                serialSend('p');
                if (temp > 0) {
                    temp--;
                }
                break;

            case 'P':
                serialSend('P');
                pres++;
                break;

            case 'p':
                serialSend('p');
                if (pres > 0) {
                    pres--;
                }
                break;


            case 'N':
                serialSend('N');
                if (lev > 0) {
                    lev--;
                }
                break;

            default:
                break;
        }
    }

}

void status(void) {//LIMITES E CONDICOES DAS GRADEZAS FISICAS, RGB E BUZZER
    if (pres > 20 || temp > 300 || lev == 0) { //pressao ou temperatura fora do aceitavel   
        PORTD = 0b00000001; //acende vermelho
        pwmSet(100);
    } else {
        pwmSet(0);
        PORTD = 0b00000010; //acende verde          
    }
}

void main() {
    TRISD = 0x00;
    char slot = 0, i;

    lcdInit();
    kpInit();
    serialInit();
    pwmInit();
    timerInit();

    pwmSet(0);
    lcdString("Iniciando...");
    tempo(10);

    lcdCommand(L_CLR);

    for (;;) {
        timerReset(3000);
        switch (slot) {//DINAMINA CODIGO
            case 0:
                leituraMenu();
                switch (menuNum) {//CONTROLE DE MENUS E SUBMENUS
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
                slot = 0;
                break;

            default:
                slot = 0;
                break;
        }
        timerWait();
    }//end for
}