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

    uint8_t id[2] = {0b11001100, 0b00000000};
    char data[3] = {0x23, 0x11, 0xF3};
    can_controller_load_tx_buffer(id, data, 3, 0);

    printf("higher = %x \n", can_controller_read(0x31));
    printf("lower = %x \n", can_controller_read(0x32));

    can_controller_load_tx_buffer(id, data, 3, 1);
    can_controller_load_tx_buffer(id, data, 3, 2);


    for (int i = 0; i < 3; i++) {
        uint8_t addr = 0x36 + i;
        printf("buffer0 = %x \n", can_controller_read(addr));
    }

    for (int i = 0; i < 3; i++) {
        uint8_t addr = 0x46 + i;
        printf("buffer1 = %x \n", can_controller_read(addr));
    }

    for (int i = 0; i < 3; i++) {
        uint8_t addr = 0x56 + i;
        printf("buffer2 = %x \n", can_controller_read(addr));
    }

    while(1){
        _delay_ms(500);
        OLED_clear_screen();
        draw_menu();
        OLED_update_screen();


    }
    return 0;
}