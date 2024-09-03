#include "avr/io.h"
#include "util/delay.h"

int main(){
    
    while(1){
    DDRA |= (1<<PA0); //sets PA0 as output
    PORTA |= (1<<PA0); //sets PA0 high

    _delay_ms(1);
    DDRA |= (1<<PA0); //sets PA0 as output
    PORTA |= (0<<PA0); //sets PA0 high

    _delay_ms(1);
    }

    return 0;
}

