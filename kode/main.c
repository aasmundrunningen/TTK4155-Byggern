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
    spi_init();


    sei(); //enables global interrupts

    while(1){
        _delay_ms(500);
        OLED_clear_screen();
        draw_menu();
        OLED_update_screen();

        char data_2[3] = {0x02, 0x0f, 0x40}; //set status register as loopback with no interrupt
        spi_transmitt_recive(data_2, 3);
        char data[3] = {0x03, 0x0E, 0x00};
        spi_transmitt_recive(data, 3);
        printf("%x, %x, %x\n", (uint8_t)data[0], (uint8_t)data[1], (uint8_t)data[2]);
    }
    return 0;
}