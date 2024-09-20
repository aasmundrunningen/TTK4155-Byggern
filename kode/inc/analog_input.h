#pragma once
#include "avr/io.h"

typedef struct {
    int16_t x_percentage;
    int16_t y_percentage;
    int16_t left_slider_percetage;
    int16_t right_slider_percetage; 
} input_value;


typedef struct {
    uint8_t x_dir;
    uint8_t y_dir;
} joystick_offset;

typedef enum {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NEUTRAL
} joystick_direction;

void joystick_slider_init(joystick_offset* offset, joystick_direction * joystick_dir, input_value * joystick_slider_values);
void calibrate_joystick(joystick_offset* offset);

void update_joystick_slider_values(input_value* values, joystick_offset* offset);
void calculate_joystick_direction(input_value* values, joystick_direction* dir);

void print_dir(joystick_direction* dir);
void print_xy(input_value* values);