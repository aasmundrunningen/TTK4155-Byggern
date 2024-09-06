//definition of all kinds of interrupt handlers

#include "usart.h"

char uart_data;
ISR(USART0_RXC_vect, ISR_BLOCK){
    USART0_RX_IRQ_Handler();
    uart_data = UDR0;
}