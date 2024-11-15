#include "config.h"
#include "avr/io.h"
#include "utilities.h"

void utilities_init(){
    set_bit(DDRB, PIN0); //enables heart_beat as output
}
int heart_beat_status = 0;
void heart_beat(){
    if(heart_beat_status == 1){
        set_bit(PORTB, PIN0);
        heart_beat_status = 0;
    }else{
        clear_bit(PORTB, PIN0);
        heart_beat_status = 1;
    }
}