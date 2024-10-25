
#include "avr/io.h"
#include "util/delay.h"

#include "config.h"
#include "usart.h"

#include "analog_input.h"
#include "avr/interrupt.h"
#include "SRAM.h"
#include "adc.h"
#include "OLED.h"
#include <stdlib.h>
#include "timer.h"
#include "pwm.h"
#include "can_controller.h"
#include "can.h"
#include "spi.h"

#include "utilities.h"



char buffer[8];


int main(){
    utilities_init();
    pwm_init();
    USART0_Init();
    
    SRAM_init();
    
    analog_init();
    
    timer0_enable_IRQ();
    USART0_RX_IRQ_Enable(&buffer, 1);

    OLED_init();
    can_controller_init();

    sei(); //enables global interrupts

    //can_controller_test();
   
    while(1){
        heart_beat();
        
        _delay_ms(2000);
        OLED_clear_screen();
        draw_menu();
        OLED_update_screen();
        can_transmitt_joystick();
    }
    return 0;
}