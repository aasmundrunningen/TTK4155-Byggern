#include "config.h"
#include "avr/io.h"
#include "util/delay.h"
#include "usart.h"
#include "avr/interrupt.h"

char buffer[8];

int main(){
    //set_bit(DDRA, PA0);
    USART0_Init();
    
    sei(); //enables global interrupts
    USART0_RX_IRQ_Enable(&buffer, 8);

    while(1){
        if(USART0_RX_DATA_Ready()){
            for(int i = 0; i < 8; i++){
                printf("%c",buffer[i]);
            }
            printf("\n");
            USART0_RX_IRQ_Enable(&buffer, 8);

        }
        /*set_bit(PORTA, PA0);
        _delay_ms(100);
        
        clear_bit(PORTA, PA0);
        _delay_ms(100); 

        USART0_Transmit('a');*/
        //char c = USART0_Poll_Receive(NULL);
        
        //clear_bit(PORTA, PA0);
        //_delay_ms(10);
        //printf("h");
        //_delay_ms(10);
    }

    return 0;
}

