#include "config.h"
#include "sam.h"

#include "encoder.h"
#include <stdio.h>

int32_t encoder_offsett = 0;

void encoder_init(void) {
    //enables the clocks for the channels
    PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_CMD | ID_TC6; //TC2, channel 0: ugly id
    PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_CMD | ID_TC7; //TC2, channel 1: ugly id
    // Disable PIO functions
    PIOB->PIO_PDR   |=   PIO_PC25 | PIO_PC26;
    // Set peripheral B instead of A for pin PC25 and PC26
    PIOB->PIO_ABSR  |= PIO_PC25 | PIO_PC26;

    // Enable cloack on A and B for TC2 channel 0
    TC2->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN;

    TC2->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_XC0 | TC_CMR_ETRGEDG_RISING | TC_CMR_ABETRG;
    TC2->TC_BMR = TC_BMR_POSEN | TC_BMR_QDEN | TC_BMR_EDGPHA;

    TC2->TC_CHANNEL[0].TC_CCR |= TC_CCR_SWTRG;
}

void update_encoder_data(void) {
    return;
}

int32_t fetch_encoder_data(void){
    return TC2->TC_CHANNEL[0].TC_CV - encoder_offsett;
}

void encoder_set_offsett(){
    encoder_offsett = TC2->TC_CHANNEL[0].TC_CV;
}
void encoder_addjust_offsett(int32_t addjustment){
    encoder_offsett += addjustment;
}