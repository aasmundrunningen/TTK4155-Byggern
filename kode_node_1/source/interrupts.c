//definition of all kinds of interrupt handlers

#include "usart.h"
#include "timer.h"
#include "can_controller.h"
#include "analog_input.h"

char uart_data;
ISR(USART0_RXC_vect, ISR_BLOCK){
    USART0_RX_IRQ_Handler();
    uart_data = UDR0;
}

ISR(TIMER0_COMP_vect, ISR_BLOCK){
    timer0_IRQ_handler();
}

ISR(INT0_vect, ISR_BLOCK){
    can_controller_IRQ_handler();
}

ISR(INT1_vect, ISR_BLOCK) {
    button_interrupt_handler();
}