#include "analog_input.h"
#include "config.h"
#include "adc.h"
#include "avr/io.h"
#include <stdio.h>
#include <stdlib.h>

void calibrate_joystick(joystick_offset* offset) {
    adc_update();
    offset->x_dir = get_adc_data(0);
    offset->y_dir = get_adc_data(1);
    return;
}

void joystick_slider_init(joystick_offset* offset, joystick_direction * joystick_dir, input_value * joystick_slider_values) {
    
    //input_value * joystick_slider_values = (input_value*)malloc(sizeof(input_value));
    joystick_slider_values->x_percentage = 0;
    joystick_slider_values->y_percentage = 0;
    joystick_slider_values->left_slider_percetage = 0;
    joystick_slider_values->right_slider_percetage = 0;

    //joystick_direction * joystick_dir = (joystick_direction*)malloc(sizeof(joystick_direction));
    *joystick_dir = NEUTRAL;    

    //joystick_offset* offset = (joystick_offset*)malloc(sizeof(joystick_offset*));
    offset->x_dir = 0;
    offset->y_dir = 0;
    #ifdef JOYSTICK_CALIBRATION
        calibrate_joystick(offset);
    #endif
}

void calculate_joystick_direction(input_value* values, joystick_direction* dir) {
    uint8_t deadzone = JOYSTICK_deadzone;
    if (abs(values->x_percentage) < deadzone && abs(values->y_percentage) < deadzone) {
        *dir = NEUTRAL;
        return;
    } 

    if (abs(values->y_percentage) - abs(values->x_percentage) > 0) {
        if (values->y_percentage > 0) {
            *dir = UP;
            return;
        } else {
            *dir = DOWN;
            return;
        }
    } else {
        if (values->x_percentage > 0) {
            *dir = RIGHT;
            return;
        } else {
            *dir = LEFT;
            return;
        }
    }
}
void update_joystick_slider_values(input_value* values, joystick_offset* offset) {
    adc_update();
    values->x_percentage = ((int16_t)(get_adc_data(0) - offset->x_dir)*100/128);
    values->y_percentage = ((int16_t)(get_adc_data(1) - offset->y_dir)*100/128);
    values->left_slider_percetage = get_adc_data(2);
    values->right_slider_percetage = get_adc_data(3);
    return;
}

void print_dir(joystick_direction* dir) {
    printf(dir);
};
void print_xy(input_value* values) {
    printf("%i   %i \n", values->x_percentage, values->y_percentage);
}