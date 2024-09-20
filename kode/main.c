#include "config.h"
#include "avr/io.h"
#include "util/delay.h"
#include "usart.h"
#include "analog_input.h"
#include "avr/interrupt.h"
#include "SRAM.h"
#include "adc.h"
#include <stdlib.h>

char buffer[8];

volatile char *oled = (char *) OLED_start_command;
joystick_offset offset;
joystick_direction joystick_dir;
input_value joystick_slider_values;

int main(){
    USART0_Init();
    SRAM_init();
    adc_init();
    joystick_slider_init(&offset, &joystick_dir, &joystick_slider_values);
    //SRAM_test();

    USART0_RX_IRQ_Enable(&buffer, 1);
    sei(); //enables global interrupts

    while(1){
        _delay_ms(500);
        update_joystick_slider_values(&joystick_slider_values, &offset);
        calculate_joystick_direction(&joystick_slider_values, &joystick_dir);

        print_xy(&joystick_slider_values);
        //print_dir(&joystick_dir);        
        //SRAM_test();


    }
    return 0;
}

