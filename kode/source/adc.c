#include "avr/io.h"
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "util/delay.h"

uint8_t adc_data[3] = {3,3,3,3};
volatile uint8_t* adc = (uint8_t*)ADC_address;

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