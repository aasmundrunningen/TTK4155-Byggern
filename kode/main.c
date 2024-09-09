#include "config.h"
#include "avr/io.h"
#include "util/delay.h"
#include "usart.h"
#include "avr/interrupt.h"
#include "SRAM.h"

char buffer[8];

int main(){
    USART0_Init();
    SRAM_init();
    //SRAM_test();

    USART0_RX_IRQ_Enable(&buffer, 1);
    sei(); //enables global interrupts

    
    
    
    while(1){
        _delay_ms(2000);
    };
    return 0;
}

