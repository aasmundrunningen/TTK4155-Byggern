#pragma once
#include <stdbool>

typedef struct {
    int x_percentage;
    int y_percentage;
} input_value;

typedef enum {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NEUTRAL
} joystick_direction;

void joystick_init(bool calibration);
void calibrate_joystick();

void update_joystick_values(input_value* values);
void calculate_joystick_direction(input_value* values, joystick_direction* dir);