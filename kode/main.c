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
    //print_letter('f', 0, 0);
    //print_letter('h', 0, 127-7);
    //print_letter('h', 1, 0);
    //print_letter('f', 7, 127-7);
    //print_letter('h', 7, 127-7);
    for(int i = 0; i < 128; i++){
        //print_byte(0b11111110 + i%2, 0, i);
        //print_byte(0b01111011 + (i%2 << 7), 7, i);
        //print_byte(0b01011011 + (i%2 << 7), 7, i);
    }
    OLED_update_screen();
    sei(); //enables global interrupts


    while(1){
        _delay_ms(500);
        //update_analog_values();
        //calculate_joystick_direction();
        //print_joystick();
        //print_slider();
        //SRAM_test();
        //printf_oled('I', 1,BIG);
        //test_oled();
        //print_letter('f');

    }
    return 0;
}




print_letter(, inverted)
print_line(solid, dashed)
print_string(med nevvline)