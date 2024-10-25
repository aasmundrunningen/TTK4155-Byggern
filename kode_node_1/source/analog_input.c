#include "analog_input.h"
#include "config.h"
#include "adc.h"
#include "util/delay.h"
#include "avr/io.h"
#include <stdio.h>
#include <stdlib.h>

ANALOG_DATA analog_data;

void calibrate_joystick() {
    printf("calibrating joystick: ");
    adc_update();
    analog_data.joystick_offsett_x = 0;
    analog_data.joystick_offsett_y = 0;
    for(int i = 0; i < JOYSTICK_CALIBRATION_SAMPLES; i++){
        analog_data.joystick_offsett_x += get_adc_data(0);
        analog_data.joystick_offsett_y += get_adc_data(1);
        _delay_ms(1);
    }
    analog_data.joystick_offsett_x = analog_data.joystick_offsett_x/JOYSTICK_CALIBRATION_SAMPLES;
    analog_data.joystick_offsett_y = analog_data.joystick_offsett_y/JOYSTICK_CALIBRATION_SAMPLES;
    //printf("offsett_x: %i   offsett_y: %i\n", analog_data.joystick_offsett_x, analog_data.joystick_offsett_y);
    return;
}

void analog_init(){
    analog_data.joystick_offsett_x = 0;
    analog_data.joystick_offsett_y = 0;
    analog_data.joystick_x = 0;
    analog_data.joystick_y = 0;
    analog_data.slider_1 = 0;
    analog_data.slider_2 = 0;
    analog_data.joystick_direction = NEUTRAL;print_joystick();


    #ifdef JOYSTICK_CALIBRATION
        calibrate_joystick();
    #endif
}

void calculate_joystick_direction(){
    if (abs(analog_data.joystick_x) < JOYSTICK_deadzone && abs(analog_data.joystick_y) < JOYSTICK_deadzone) {
        analog_data.joystick_direction = NEUTRAL;
        return;adc_update();
    } 

    if (abs(analog_data.joystick_y) - abs(analog_data.joystick_x) > 0) {
        if (analog_data.joystick_y > 0) {
            analog_data.joystick_direction = UP;
            return;
        } else {
            analog_data.joystick_direction = DOWN;
            return;
        }
    } else {
        if (analog_data.joystick_x > 0) {
            analog_data.joystick_direction = RIGHT;
            return;
        } else {
            analog_data.joystick_direction = LEFT;
            return;
        }
    }
}
void update_analog_values() {
    adc_update();
    int16_t temp_x = ((int16_t)(get_adc_data(0) - analog_data.joystick_offsett_x));
    int16_t temp_y = ((int16_t)(get_adc_data(1) - analog_data.joystick_offsett_y));
    //some currsed shit with hardware, different scalling off values.
    //It scales correct for low values but high values need scaling
    if(temp_x > 0){
        temp_x = temp_x*100/156;
    }
    if(temp_y > 0){
        temp_y = temp_y*100/156;
    }
    
    if(temp_x < -100){
        temp_x = -100;
    }
    if(temp_y < -100){
        temp_y = -100;
    }
    if(temp_x > 100){
        temp_x = 100;
    }
    if(temp_y > 100){
        temp_y = 100;
    }

    analog_data.joystick_x = (int8_t)temp_x;
    analog_data.joystick_y = (int8_t)temp_y;
    
    analog_data.slider_1 = get_adc_data(2);
    analog_data.slider_2 = get_adc_data(3);
    calculate_joystick_direction();
    return;
}

void print_joystick() {
    printf("joystick_data: direction: %s, x: %i, y: %i, slider 1: %i, slider 2: %i\n", 
        JOYSTICK_DIRECTION_string[analog_data.joystick_direction], 
        analog_data.joystick_x, 
        analog_data.joystick_y,
        analog_data.slider_1,
        analog_data.slider_2);
}

void print_slider(){
    printf("Slider 1: %i, Slider 2: %i\n",
        analog_data.slider_1,
        analog_data.slider_2);
}

ANALOG_DATA get_analog_data(){
    return analog_data;
}