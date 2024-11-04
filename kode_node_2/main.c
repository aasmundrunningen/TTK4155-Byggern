#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "sam.h"
#include "config.h"
#include "uart.h"
#include "can.h"
#include "pwm.h"
#include "adc.h"
#include "time.h"

#include "game_engine.h"
#include "analog_data.h"

//Import UART from Node 2 starter code, then edit include path accordingly. Also, remember to update the makefile
//#include "uart.h"

CanMsg can_message;

ANALOG_DATA rx_data;

void delay(uint32_t t){
    volatile uint32_t a;
    while(a < t * F_CPU/1000){
        a += 1;
    }
}

int main()
{
    SystemInit();
    uart_init(CPU_FREQ, UART_BAUDRATE);
    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer
    CanInit can_init_register = {1, 0, 1, 2, 68, 1};
    can_init(can_init_register, 0);
    pwm_init();
    adc_init();

    //configure_uart();
    uint64_t last_printf = 0;
    uint32_t time_32b = 0;
    while (1) {
        //delay(10000);
        //printf("%d\n",adc_read());
        if(can_rx(&can_message) == 1){
            memcpy(&rx_data, can_message.byte8.bytes,8);
            /*printf("x:%d, y:%d, slider1:%d, slider2:%d\n",
                rx_data.joystick_x,
                rx_data.joystick_y,
                rx_data.slider_1,
                rx_data.slider_2);
            */
           //printf("x:%d, y:%d\n", rx_data.joystick_x, rx_data.joystick_y);
        }
        pwm_set_duty(rx_data.joystick_x);
        score_counter();
       
        //time_32b = (uint32_t)time_now();
        //printf("%ld\n", seconds(time_now()));
        /*uint64_t time_ms = msecs(time);
        if((uint32_t)last_printf + (uint32_t)1000 < (uint32_t)time_ms){
            //printf("game_data: %d, %d\n", get_game_data().score, get_game_data().last_point_time);
            last_printf = msecs(time);
            printf("hei %d \n", last_printf);
        }*/
       printf("%d\n", get_game_data().score);
        
        
    }
}