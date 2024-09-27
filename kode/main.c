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
    
    OLED_init();
    //OLED_update_screen();
    sei(); //enables global interrupts


    while(1){
        _delay_ms(500);
        //update_analog_values();
        //calculate_joystick_direction();
        //print_joystick();
        //print_slider();
        //SRAM_test();
        //printf_oled('I', 1,BIG);

        //print_letter('f');
        //test_oled();

    }
    return 0;
}

