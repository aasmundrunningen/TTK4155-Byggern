#include "config.h"
#include "avr/io.h"
#include "util/delay.h"
#include "usart.h"
#include "analog_input.h"
#include "avr/interrupt.h"
#include "SRAM.h"
#include "adc.h"
#include "OLED.h"
#include <stdlib.h>
#include "timer.h"
char buffer[8];

int main(){
    USART0_Init();
    SRAM_init();
    adc_init();
    analog_init();
    //SRAM_test();

    timer0_enable_IRQ();
    USART0_RX_IRQ_Enable(&buffer, 1);
    sei(); //enables global interrupts


    OLED_init();

    while(1){
        _delay_ms(500);
    }
    return 0;
}