#include "config.h"
#include "delay.h"

void tempo(unsigned char tempX){
    volatile unsigned char i, j, k, aux;
  
    for(aux= 0; aux < tempX; aux++){
        for(i = 0; i < 100; i++) { 
            for(j = 0; j < 41; j++) { 
                for(k = 0; k < 3; k++); 
            }
        }
    }
}


