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
#include "encoder.h"
#include "motor_controller.h"
#include "utilities.h"

CanMsg can_message;

ANALOG_DATA rx_data;



int main()
{
    SystemInit();
    uart_init(CPU_FREQ, UART_BAUDRATE);
    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer
    CanInit can_init_register = {1, 0, 1, 2, 68, 1};
    CanMsg CAN_score = {.id = 2, .length = 8};
    can_init(can_init_register, 0);
    pwm_init();
    adc_init();
    encoder_init();
    motor_controller_init();

    __enable_irq();
    TC0_enable_interrupt();

    uint64_t last_printf = 0;
    uint32_t time_32b = 0;
    while (1) {
        if(can_rx(&can_message) == 1){
            memcpy(&rx_data, can_message.byte8.bytes,8);
        }
        pwm_set_duty(-rx_data.joystick_x);
        if(rx_data.solenoid_state == 1){
            activate_solenoid();
        }
        score_counter();
        CAN_score.byte[0] = get_game_data().score;
        can_tx(CAN_score);
        motor_controller_set_sp(rx_data.joystick_y);
        
    }
}