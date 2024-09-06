#include "config.h"
#include "avr/io.h"
#include "util/delay.h"
#include "usart.h"

#define set_bit(reg,bit )( reg |= ( 1 <<bit))
#define clear_bit( reg , bit )( reg &= ~(1 << bit ))
#define test_bit( reg , bit )( reg & ( 1 <<bit ))
//#define loop_until_bit_is_set(reg,bit) while(!test_bit (reg , bit))
//#define loop_until_bit_is_clear(reg,bit) while(test_bit(reg,bit))


int main(){
    set_bit(DDRA, PA0);
    USART0_Init();
    

    while(1){
        /*set_bit(PORTA, PA0);
        _delay_ms(100);
        
        clear_bit(PORTA, PA0);
        _delay_ms(100); 

        USART0_Transmit('a');*/
        printf("hello this\n");
        _delay_ms(100);
    }

    return 0;
}

