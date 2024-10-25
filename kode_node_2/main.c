#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "sam.h"
#include "config.h"
#include "uart.h"
#include "can.h"


#include "analog_data.h"

//Import UART from Node 2 starter code, then edit include path accordingly. Also, remember to update the makefile
//#include "uart.h"

CanMsg can_message;

ANALOG_DATA rx_data;

int main()
{
    SystemInit();
    uart_init(CPU_FREQ, UART_BAUDRATE);
    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer
    CanInit can_init_register = {1, 0, 1, 2, 68, 1};
    can_init(can_init_register, 0);

    //configure_uart();
    printf("Hello World\n");

    while (1) {
        if(can_rx(&can_message) == 1){
            memcpy(&rx_data, can_message.byte8.bytes,8);
            printf("x:%d, y:%d, slider1:%d, slider2:%d\n",
                rx_data.joystick_x,
                rx_data.joystick_y,
                rx_data.slider_1,
                rx_data.slider_2);
        }
    }
}