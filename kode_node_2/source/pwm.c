#include "sam.h"
#include "sam/io.h"
#include "config.h"
#include "pwm.h"

#include <stdint.h>

// PWM Register Structure
typedef struct {
    volatile uint32_t PWM_CLK;           // 0x00: PWM Clock Register
    volatile uint32_t PWM_ENA;           // 0x04: PWM Enable Register
    volatile uint32_t PWM_DIS;           // 0x08: PWM Disable Register
    volatile uint32_t PWM_SR;            // 0x0C: PWM Status Register
    volatile uint32_t PWM_IER1;          // 0x10: PWM Interrupt Enable Register 1
    volatile uint32_t PWM_IDR1;          // 0x14: PWM Interrupt Disable Register 1
    volatile uint32_t PWM_IMR1;          // 0x18: PWM Interrupt Mask Register 1
    volatile uint32_t PWM_ISR1;          // 0x1C: PWM Interrupt Status Register 1
    volatile uint32_t PWM_SCM;           // 0x20: PWM Sync Channels Mode Register
    volatile uint32_t Reserved1;         // 0x24: Reserved
    volatile uint32_t PWM_SCUC;          // 0x28: PWM Sync Channels Update Control Register
    volatile uint32_t PWM_SCUP;          // 0x2C: PWM Sync Channels Update Period Register
    volatile uint32_t PWM_SCUPUPD;       // 0x30: PWM Sync Channels Update Period Update Register
    volatile uint32_t PWM_IER2;          // 0x34: PWM Interrupt Enable Register 2
    volatile uint32_t PWM_IDR2;          // 0x38: PWM Interrupt Disable Register 2
    volatile uint32_t PWM_IMR2;          // 0x3C: PWM Interrupt Mask Register 2
    volatile uint32_t PWM_ISR2;          // 0x40: PWM Interrupt Status Register 2
    volatile uint32_t PWM_OOV;           // 0x44: PWM Output Override Value Register
    volatile uint32_t PWM_OS;            // 0x48: PWM Output Selection Register
    volatile uint32_t PWM_OSS;           // 0x4C: PWM Output Selection Set Register
    volatile uint32_t PWM_OSC;           // 0x50:
    volatile uint32_t PWM_OSSUPD;        // 0x54
    volatile uint32_t PWM_OSCUPD;        // 0x58: PWM Output Selection Clear Update Register
    volatile uint32_t PWM_FMR;           // 0x5C: PWM Fault Mode Register
    volatile uint32_t PWM_FSR;           // 0x60: PWM Fault Status Register
    volatile uint32_t PWM_FCR;           // 0x64: PWM Fault Clear Register
    volatile uint32_t PWM_FPV;           // 0x68: PWM Fault Protection Value Register
    volatile uint32_t PWM_FPE1;          // 0x6C: PWM Fault Protection Enable Register 1
    volatile uint32_t PWM_FPE2;          // 0x70: PWM Fault Protection Enable Register 2
    uint32_t Reserved2[2];               // 0x74 - 0x78: Reserved
    volatile uint32_t PWM_ELMR[2];       // 0x7C - 0x80: PWM Event Line Mode Register 0 - 1
    uint32_t Reserved3[11];              // 0x84 - 0xAC: Reserved
    volatile uint32_t PWM_SMMR;                   //0xB0
    volatile uint32_t Reserved7[12];      // 0xB4-E0
    volatile uint32_t PWM_WPCR;          // 0xE4: PWM Write Protect Control Register
    volatile uint32_t PWM_WPSR;          // 0xE8: PWM Write Protect Status Register
    uint32_t Reserved4[5];               // 0xEC - 0xFC: Reserved
    uint32_t Reserved5[12];              // 0x100 - 0x128: Reserved for PDC Registers
    volatile uint32_t PWM_CMPV[8];       // 0x130 - 0x14C: PWM Comparison Value Register 0 - 7
    volatile uint32_t PWM_CMPVUPD[8];    // 0x150 - 0x16C: PWM Comparison Value Update Register 0 - 7
    volatile uint32_t PWM_CMPM[8];       // 0x170 - 0x18C: PWM Comparison Mode Register 0 - 7
    volatile uint32_t PWM_CMPMUPD[8];    // 0x190 - 0x1AC: PWM Comparison Mode Update Register 0 - 7
    uint32_t Reserved6[20];              // 0x1B0 - 0x1FC: Reserved

    // Indexed Registers (using ch_num from 0 to 7)
    struct {
        volatile uint32_t CMR;           // 0x200 + 0x20 * ch_num: PWM Channel Mode Register
        volatile uint32_t CDTY;          // 0x204 + 0x20 * ch_num: PWM Channel Duty Cycle Register
        volatile uint32_t CDTYUPD;       // 0x208 + 0x20 * ch_num: PWM Channel Duty Cycle Update Register
        volatile uint32_t CPRD;          // 0x20C + 0x20 * ch_num: PWM Channel Period Register
        volatile uint32_t CPRDUPD;       // 0x210 + 0x20 * ch_num: PWM Channel Period Update Register
        volatile uint32_t CCNT;          // 0x214 + 0x20 * ch_num: PWM Channel Counter Register
        volatile uint32_t DT;            // 0x218 + 0x20 * ch_num: PWM Channel Dead Time Register
        volatile uint32_t DTUPD;         // 0x21C + 0x20 * ch_num: PWM Channel Dead Time Update Register
    } Channel[8];
} PWM_Registers;

PWM_Registers *PWM_reg = (PWM_Registers*)PWM;

#define PWM_PERIODE 52500
#define PWM_MIN_DUTY_CYCLE (uint32_t)(PWM_PERIODE * 9/200)
#define PWM_MAX_DUTY_CUCLE (uint32_t)(PWM_PERIODE * 21/200)


void pwm_init(){
    // Enables the PWM clock in PMC
    PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_CMD | ID_PWM; 

    // Write protected ????
    // Disable PIO functions
    PIOB->PIO_PDR   |=   PIO_PB13 | PIO_PB17;
    // Set peripheral B instead of A for pin 13 and 17
    PIOB->PIO_ABSR  &= PIO_PB13 | PIO_PB17;



    //write 0 to WPCMD disabling write protection

    //writing "PWM" to WPKEY and 0 to WPCMD dissabling write protection
    PWM_reg->PWM_WPCR = 0x5057AD00;
    

    //set channel 1 clock to master clock/32
    clear_byte(PWM_reg->Channel[1].CMR, 0);
    set_byte(PWM_reg->Channel[1].CMR, 0, 0b101);
    
    //set left aligned waveform
    clear_bit(PWM_reg->Channel[1].CMR, 8);

    clear_bit(PWM_reg->Channel[1].CMR, 9);    

    //set channel periode register to PWM_PERIODE giving 20mS periode
    PWM_reg->Channel[1].CPRD = PWM_PERIODE;

    //set duty cycle to PWM_MIN_DUTY_CUCLE
    PWM_reg->Channel[1].CDTY = 30000;//PWM_MIN_DUTY_CYCLE;

    //set deadtime to 0
    PWM_reg->Channel[1].DT = 0;

    //dissable all syncronazationPWM_reg->PWM_WPCR
    PWM_reg->PWM_SCM = 0;

    //enables channel 1
    set_bit(PWM_reg->PWM_ENA, 1);

}

void pwm_print_status(){
    printf("WPSR: %x, address: %x \n", PWM_reg->PWM_WPSR, &(PWM_reg->PWM_WPSR));
    printf("PMC_STATUS 0: %x \n", *(uint32_t*)0x400E0618);
    printf("PMC_STATUS 1: %x \n", *(uint32_t*)0x400E0708);
    printf("PIO_STATUS: %x \n", *(uint32_t*)0x400E1008);
    printf("PWM_status: %x \n", *(uint32_t*)0x4009400C);
        

    int volatile * reg = (int *)0x400E0618;
}

