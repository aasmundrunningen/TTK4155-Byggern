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
#include "pwm.h"
#include "can_controller.h"
#include "can.h"

#include "spi.h"

char buffer[8];


int main(){
    pwm_init();
    USART0_Init();
    SRAM_init();
    analog_init();

    timer0_enable_IRQ();
    USART0_RX_IRQ_Enable(&buffer, 1);

    OLED_init();

    sei(); //enables global interrupts

    can_controller_init();

    //can_controller_test();

    CAN_MESSAGE can_message;
    strcpy(can_message.data, "hei");
    can_message.length = 3;
    can_message.id = 1;
    while(1){
        _delay_ms(500);
        OLED_clear_screen();
        draw_menu();
        OLED_update_screen();
        //can_controller_send(can_message, 0);
        can_transmitt_joystick();
    }
    return 0;
}