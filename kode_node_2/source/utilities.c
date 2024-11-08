#include <stdio.h>
#include "config.h"
void delay_ms(uint32_t t){
    for(volatile uint32_t a = 0; a<(t*F_CPU/1000); a+=9){//asm("NOP");
    }
}