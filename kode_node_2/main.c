#include <stdio.h>
#include <stdarg.h>
#include "sam.h"
#include "config.h"
#include "uart.h"
#include "can.h"

//Import UART from Node 2 starter code, then edit include path accordingly. Also, remember to update the makefile
//#include "uart.h"

CanMsg can_message;


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
            printf("recived can message: id: %d, data:", can_message.id);
            printf("x: %d, y: %d, dir: %d, s1: %u, s2: %u\n", 
                can_message.byte8.bytes[0], 
                can_message.byte8.bytes[1], 
                can_message.byte8.bytes[2], 
                can_message.byte8.bytes[3], 
                can_message.byte8.bytes[4]);
        }
    }
    
}