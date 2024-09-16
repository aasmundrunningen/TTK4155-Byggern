#include "config.h"
#include "avr/io.h"
#include "util/delay.h"
#include "usart.h"
#include "avr/interrupt.h"
#include "SRAM.h"

#include <stdlib.h>

char buffer[8];

volatile char *adc = (char *) ADC_address;
volatile char *oled = (char *) OLED_start_command;
int main(){
    USART0_Init();
    SRAM_init();
    //SRAM_test();

    USART0_RX_IRQ_Enable(&buffer, 1);
    sei(); //enables global interrupts

    
    
    
    while(1){
        _delay_ms(2000);
        uint8_t some_value = rand();
        adc = some_value;
        oled = some_value;

        SRAM_test();
    };
    return 0;
}

