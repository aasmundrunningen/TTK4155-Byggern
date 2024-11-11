
#include <stdio.h>
#include "pwm.h"
#include "config.h"
#include "encoder.h"
#include "utilities.h"
#include "motor_controller.h"


#define F_TC0_INTERRUPT 100 //in Hz
#define PID_MAX_POWER 100
#define PID_kp 1200
#define PID_ki 2

#define SOLENOID_ACTIVATION_CYCLES 10

uint32_t encoder_range = 0;

int8_t motor_sp = 0;
int8_t motor_power = 0;
int32_t motor_error_integral = 0; //given in error/ms


const int32_t PID_dt = 1000/F_TC0_INTERRUPT; //given in ms
int32_t PID_error = 0;
int32_t PID_integrated_error = 0;
int32_t PID_power = 0;
int32_t PID_sp = 0;
int32_t PID_cp = 0;

void motor_controller_init(){
    delay_ms(1000);
    pwm_motor_controll(120);
    int32_t encoder_last_value = 0;
    do{
        encoder_last_value = fetch_encoder_data();
        delay_ms(100);
    } while(encoder_last_value != fetch_encoder_data());
    delay_ms(100); //removing debounc;
    encoder_set_offsett();
    pwm_motor_controll(-120);

    do{
        encoder_last_value = fetch_encoder_data();
        delay_ms(100);
    } while(encoder_last_value != fetch_encoder_data());
    pwm_motor_controll(0);
    encoder_range = abs(fetch_encoder_data());
    encoder_addjust_offsett(-(int32_t)encoder_range/2);


    set_bit(PIOC->PIO_OER, 24); //enables direction pin as output
    set_bit(PIOC->PIO_OWER, 24); //enables direction pin as output

}

void motor_controller_set_sp(int8_t sp){
    PID_sp = (int32_t)sp * (int32_t)encoder_range/(2*100);
    //printf("SP: %d, PID_pow: %i, PID_sp: %i, PID_cp: %i, encod_rang: %i\n", sp, PID_power, PID_sp, PID_cp, encoder_range);
}

void TC0_enable_interrupt(){
    PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_CMD | ID_TC0; //TC0, channel 0: ugly id
    TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN; //enable clock

    TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_CPCTRG; //clock=MCK/2, reset clock on RC match

    TC0->TC_CHANNEL[0].TC_CCR |= TC_CCR_SWTRG;

    TC0->TC_CHANNEL[0].TC_RC = F_CPU/2 / F_TC0_INTERRUPT; //Gives the periode of the interrupt
    
    TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_SWTRG; //enable clock

    TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS; //enables interrupt on RC compare
    NVIC_EnableIRQ(ID_TC0);

}

void TC0_Handler(void){
    PID_cp = fetch_encoder_data();
    pwm_motor_controll(PID());
    uint32_t a = TC0->TC_CHANNEL[0].TC_SR;
    solenoid_controll();
}

uint8_t solenoid_state = 0;
void solenoid_controll(){
    if(solenoid_state > 0){
        clear_bit(PIOC->PIO_ODSR, 24);
        solenoid_state --;
    }else{
        set_bit(PIOC->PIO_ODSR, 24);
    }
}

void activate_solenoid(){
    if(solenoid_state == 0){
        solenoid_state = SOLENOID_ACTIVATION_CYCLES;
    }
}

int32_t PID(){
    PID_error = PID_sp - PID_cp;
    PID_power = ((PID_kp*PID_error + PID_ki*(PID_integrated_error + PID_dt*PID_error)))/10000;
    if(abs(PID_power) < PID_MAX_POWER){
        PID_integrated_error += PID_dt*PID_error;
    }else{
        if(PID_power > 0){
            PID_power = PID_MAX_POWER;
        }else{
            PID_power = -PID_MAX_POWER;
        }
    }
    return PID_power;
}

