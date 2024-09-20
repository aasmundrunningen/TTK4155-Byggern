#include "avr/io.h"
#include "config.h"


void adc_init(){
    //enable PWM

    //enables compare output mode on OC1A and not on OC1B
    set_bit(TCCR1A, COM1A0);
    clear_bit(TCCR1A, COM1A1);

    //enables fast PWM as waveform generation mode, top counter value us OCR1A
    set_bit(TCCR1A, WGM13);
    set_bit(TCCR1A, WGM12);
    set_bit(TCCR1A, WGM11);
    set_bit(TCCR1A, WGM10);

    //same as TCCR1A not sure if we need it
    set_bit(TCCR1B, WGM13);
    set_bit(TCCR1B, WGM12);
    set_bit(TCCR1B, WGM11);
    set_bit(TCCR1B, WGM10); 

    set_bit(TCCR1B, CS10); //enalbes clock as CLK_io with no prescaling
    
    //sets the max value for the counter before reset
    OCR1AL = 0x10;
    OCR1AH = 0x00; 

}