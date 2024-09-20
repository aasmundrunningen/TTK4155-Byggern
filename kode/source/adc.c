#include "avr/io.h"
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "util/delay.h"

uint8_t adc_data[3] = {3,3,3,3};
volatile uint8_t* adc = (uint8_t*)ADC_address;

void adc_init(){
    //enable PWM
    //-----------------------
    set_bit(DDRD, PD5);
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

    //enables compare output mode on OC1A and not on OC1B
    set_bit(TCCR1A, COM1A0);
    clear_bit(TCCR1A, COM1A1);

}


void adc_update(){
    *adc = 1;
    _delay_us(50); //conversion time 120ms
    for(int i = 0; i < 4; i++){
        adc_data[i] = *adc;
    }
}

void print_adc(){
    printf("%i  %i   %i   %i \n", adc_data[0], adc_data[1], adc_data[2], adc_data[3]);
}

uint8_t get_adc_data(int index) {
    return adc_data[index];
}