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
        //_delay_ms(500);
        /*ANALOG_DATA data = get_analog_data();
        OLED_clear_screen();
        OLED_print_string("x:", 2, 0, 0, 0);
        if(data.joystick_x < 0){
            OLED_print_line(17 + 50 - data.joystick_x/2, 1, 0, 0);    
        }
        OLED_print_line(17 + 50, 1, (uint8_t)data.joystick_x/2, 0);
        OLED_print_string("y:", 2, 0, 1, 0);*/
    }
}