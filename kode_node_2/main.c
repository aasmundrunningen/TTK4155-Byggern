#include <stdio.h>
#include <stdarg.h>
#include "sam.h"
#include "config.h"
#include "uart.h"

//Import UART from Node 2 starter code, then edit include path accordingly. Also, remember to update the makefile
//#include "uart.h"

int main()
{
    SystemInit();
    uart_init(CPU_FREQ, UART_BAUDRATE);
    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

    //configure_uart();
    printf("Hello World\n");

    while (1) {

    }
    
}