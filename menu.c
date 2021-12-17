#include <proc/pic18f4520.h>
#include "config.h"
#include "bits.h"
#include "delay.h"
#include "lcd.h"
#include "serial.h"
#include "keypad.h"

#define L_ON	0x0F
#define L_OFF	0x08
#define L_CLR	0x01
#define L_L1	0x80
#define L_L2	0xC0
#define menuMax 3

char menuNum = 1, subMenu = 1;
char count, ctrl;
unsigned int aux, aux2;

unsigned int pres, temp;
unsigned char lev;

void leituraMenu() {
    if (kpRead() != aux) {
        aux = kpRead();
        if (kpReadKey() != 0) {//se alguma tecla foi precionada
            count = kpReadKey(); //armazena 

            if ((count == 'R')&&(subMenu == 1)) {
                if (menuNum <= menuMax) {
                    menuNum += 1;
                }
            }
            if ((count == 'L')&&(subMenu == 1)) {
                if (menuNum > 0) {
                    menuNum -= 1;
                }
            }
            if (count == 's') {
                if (subMenu <= 2) {
                    subMenu += 1;
                }
            }
            if (count == 'S') {
                if (subMenu > 0) {
                    subMenu -= 1;
                }
            }
        }
    }//end if (varredura)
}

void menu1(char subMenu) {
    switch (subMenu) {
        case 1:
            lcdCommand(L_L1);
            lcdString("  Temperatura  >");
            lcdCommand(L_L2);
            lcdString("                ");
            break;
        case 2:
            lcdCommand(L_L1);
            lcdString("  Temperatura:  ");
            lcdCommand(L_L2);
            lcdString("    ");
            lcdNumber(temp);
            lcdString(" ºC     ");
            break;
    }
}

void menu2(char subMenu) {
    switch (subMenu) {
        case 1:
            lcdCommand(L_L1);
            lcdString("<    Pressao   >");
            lcdCommand(L_L2);
            lcdString("                ");
            break;
        case 2:
            lcdCommand(L_L1);
            lcdString("    Pressao:    ");
            ;
            lcdCommand(L_L2);
            lcdString("    ");
            lcdNumber(pres);
            lcdString(" bar    ");
            break;
    }
}

void menu3(char subMenu) {
    switch (subMenu) {
        case 1:
            lcdCommand(L_L1);
            lcdString("<  Nivel Agua   ");
            lcdCommand(L_L2);
            lcdString("                ");
            break;
        case 2:
            lcdCommand(L_L1);
            lcdString("   Nivel Agua:  ");
            lcdCommand(L_L2);
            lcdString("    ");
            lcdNumber(lev);
            lcdString(" %      ");
            break;
    }
}

void menuCtrl(char menuNum, char subMenu) {
    if (kpRead() != aux2) {
        aux2 = kpRead(); 
        if (kpReadKey() != 0) {
            ctrl = kpReadKey(); 

            switch (ctrl) {
                case 'U':
                    if ((subMenu == 2)&&(menuNum == 1)&&(temp<280)) {
                        temp++;
                    }
                    else {
                        if ((subMenu == 2)&&(menuNum == 2)&&(pres<20)) {
                            pres++;
                        } else {
                            if ((subMenu == 2)&&(menuNum == 3)&&(lev<=100)) {
                                lev++;
                            }
                        }
                    }
                    break;

                case 'D':
                    if ((subMenu == 2)&&(menuNum == 1)&&(temp >= 0)) {
                        temp--;
                    } else {
                        if ((subMenu == 2)&&(menuNum == 2)&&(pres >= 0)) {
                            pres--;
                        } else {
                            if ((subMenu == 2)&&(menuNum == 3)&&(lev >= 0)) {
                                lev--;
                            }
                        }
                    }
                    break;

                default:
                    break;
            }
        }
    }
}//end if (varredura)
