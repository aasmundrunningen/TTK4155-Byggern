#include "avr/io.h"
#include "config.h"

void pwm_init(){
    //-----------------------
    //enable PWM on timer 1
    //-----------------------
    //same as TCCR1A not sure if we need it
    set_bit(TCCR1B, WGM13);
    set_bit(TCCR1B, WGM12);
    set_bit(TCCR1B, WGM11);
    set_bit(TCCR1B, WGM10);

    //enalbes clock as CLK_io with no prescaling
    clear_bit(TCCR1B, CS12);
    clear_bit(TCCR1B, CS11);
    set_bit(TCCR1B, CS10);
    
    //sets the max value for the counter before reset 0x0003 is the minimum value according to datasheet
    OCR1A = 0x0000;

    //enables fast PWM as waveform generation mode, top counter value us OCR1A
    set_bit(TCCR1A, WGM13);
    set_bit(TCCR1A, WGM12);
    set_bit(TCCR1A, WGM11);
    set_bit(TCCR1A, WGM10);


    //enables pwm on port PD5
    set_bit(DDRD, PD5);
    OCR1A = 0x0000; //max value for capture compare

    //enables compare output mode on OC1A and not on OC1B
    set_bit(TCCR1A, COM1A0);
    clear_bit(TCCR1A, COM1A1);

    //enables compare output mode on OC1A and not on OC1B
    //set_bit(TCCR1A, COM1A0);
    //clear_bit(TCCR1A, COM1A1);





}