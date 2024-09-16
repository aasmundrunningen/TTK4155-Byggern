#include "analog_input.h"
#include "config.h"
#include <stdbool.h>
#include <stdlib.h>

void joystick_init(bool calibration) {
    int * calibration_value = (int*)malloc(sizeof(int));
    
    input_value * joystick_xy_values = (input_value*)malloc(sizeof(input_value));
    joystick_xy_values->x_percentage = 0;
    joystick_xy_values->y_percentage = 0;

    joystick_direction * joystick_dir = (joystick_direction*)malloc(sizeof(joystick_direction));
    joystick_dir = NEUTRAL;    

    if (calibration) {
        calibrate_joystick();
    }

}

void calculate_joystick_direction(input_value* values, joystick_direction* dir) {
    if (abs(values->x_percentage) < 10 && abs(values->y_percentage) < 10) {
        dir = NEUTRAL;
        return;
    } 

    if (abs(values->y_percentage) - abs(values->x_percentage) > 0) {
        if (values->y_percentage > 0) {
            dir = UP;
            return;
        } else {
            dir = DOWN;
            return;
        }
    } else {
        if (values->x_percentage > 0) {
            dir = RIGHT;
            return;
        } else {
            dir = LEFT;
            return;
        }
    }
}
volatile char *adc = (char *) ADC_address;
void update_joystick_values(input_value* values) {
    adc = rand();

    _delay_us(20);

    //(x-128+offsett)*128/100
    values->x_percentage = adc*calibration_value + calibration_offset;
    values->y_percentage = adc*calibration_value;

    return;
}

void calibrate_joystick() {
    // calibrate the joystick
    bool calibrated = false;
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;

    while (!calibrated) {
        if (!left) {
                
            continue;
        }
    }
    return;
}
