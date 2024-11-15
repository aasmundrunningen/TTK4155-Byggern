#include "usart.h"
#include "avr/io.h"
#include "config.h"
#include <stdio.h>
#include "util/delay.h"

const unsigned int MYUBRR = F_CPU/16/BAUDRATE_UART-1; //prescaler for uart.

void USART0_Init() {
    /* Set baud rate */
    UBRR0H = (unsigned char)(MYUBRR>>8);
    UBRR0L = (unsigned char)MYUBRR;
    /* Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);

    //initialising UART0 as the standard stream, used for printf, etc.
    fdevopen(USART0_Poll_Transmit,USART0_Poll_Receive);
}

int USART0_Poll_Transmit(char data, FILE *file) {
    //ads \r when \n is writen to make it a new line on different system
    if(data == '\n'){
        USART0_Poll_Transmit('\r',NULL);
    }
    //Wait for empty transmit buffer
    while ( !( UCSR0A & (1<<UDRE0)) );
    /* Put data into buffer, sends the data */
    UDR0 = data;
    return 0;
}//set_bit(DDRA, PA0);

int USART0_Poll_Receive(FILE *file) {
    /* Wait for data to be received */
    while ( !(UCSR0A & (1<<RXC0)) );
    /* Get and return received data from buffer */
    return UDR0;
}

#ifdef UART_RX_ENABLED
char USART0_data_buffer[8];
int USART0_data_buffer_counter;
int USART0_data_buffer_size = 1;
int USART0_data_ready = 0;
char buffer[8];
void USART0_RX_IRQ_Handler(void){
    set_bit(PORTA, PA0);
    USART0_data_buffer[USART0_data_buffer_counter] = UDR0;
    USART0_data_buffer_counter ++;
    if(USART0_data_buffer_size == USART0_data_buffer_counter){
        USART0_data_buffer_counter = 0;
        clear_bit(UCSR0B, RXCIE0); //dissables the recive interrupt flag
        USART0_data_ready = 1;
    }

    #ifdef UART_CALLBACK
    USART0_Poll_Transmit(USART0_data_buffer[USART0_data_buffer_counter], NULL);
    if(USART0_data_buffer[USART0_data_buffer_counter] == '\r'){
       USART0_Poll_Transmit('\n', NULL);
    }
    #endif
    USART0_RX_IRQ_Enable();
}

int USART0_RX_DATA_Ready(){
    return USART0_data_ready;
}

void USART0_RX_IRQ_Enable(){
    USART0_data_buffer_counter = 0;
    USART0_data_ready = 0;
    set_bit(UCSR0B, RXCIE0);
}
#endif