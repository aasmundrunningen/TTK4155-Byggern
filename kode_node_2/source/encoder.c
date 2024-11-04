#include "config.h"
#include "sam.h"

#include "encoder.h"

ENCODER_DATA encoder_data = {0,0}; 

void encoder_init(void) {
    // ??? Do we need to enable clock when we disable it right after?? 
    PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_CMD | ID_TC2; 
    // Disable PIO functions
    PIOB->PIO_PDR   |=   PIO_PC25 | PIO_PC26;
    // Set peripheral B instead of A for pin 25 and 26
    PIOB->PIO_ABSR  |= PIO_PC25 | PIO_PC26;
    // PC26 PC25

    // Enable cloack on A and B for TC2 channel 0
    //REG_TC0_CCR0 = 1;
    //REG_TC0_CCR1 = 1;

    // select XC0 as clock.
    REG_TC0_CMR0 = (5 << 0);   


    /*
    -NEED TO SET clock to TCLK0

    
    
    */
    REG_TC0_BMR = 


}

void update_encoder_data(void) {
    return;
}

ENCODER_DATA fetch_encoder_data(void){
    return encoder_data;
}