#include "sam.h"
#include "sam/io.h"
#include "config.h"
#include "adc.h"


void adc_init(){
    // Enables the ADC clock in ADC
    PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_CMD | ID_ADC; 

    // Set CH0 = PA2
    //Writeprotected??????
    ADC->ADC_CHER = 1;

    //free run mode + prescaler
    ADC->ADC_MR = (1 << 7) | (10 << 8);

    //control register: start conversion
    ADC->ADC_CR = 0b10;
}

uint16_t adc_read(){
    return ADC->ADC_CDR[0];
}
