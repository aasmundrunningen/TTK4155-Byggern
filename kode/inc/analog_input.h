#pragma once
#include "avr/io.h"

typedef enum {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NEUTRAL
} JOYSTICK_DIRECTION;

static const char * JOYSTICK_DIRECTION_string[] = {
    "LEFT", "RIGHT", "UP", "DOWN", "NEUTRAL"
};


typedef struct {
    int16_t joystick_offsett_x;
    int16_t joystick_offsett_y;
    int16_t joystick_x;
    int16_t joystick_y;
    int16_t slider_1;
    int16_t slider_2;
    JOYSTICK_DIRECTION joystick_direction;
} ANALOG_DATA;

void analog_init();
void calibrate_joystick();

void update_analog_values();
void calculate_joystick_direction();

void print_slider();
void print_joystick();