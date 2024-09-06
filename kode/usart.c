#include "usart.h"
#include "avr/io.h"

#define FOSC 4915000UL// Clock Speed
#define BAUD 9600
const unsigned int MYUBRR = FOSC/16/BAUD-1;

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
}

int USART0_Poll_Receive(FILE *file) {
    /* Wait for data to be received */
    while ( !(UCSR0A & (1<<RXC0)) );
    /* Get and return received data from buffer */
    return UDR0;
}