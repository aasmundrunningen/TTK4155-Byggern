#pragma once
#include "avr/io.h"

#include "analog_data.h"

void analog_init();
void calibrate_joystick();

void update_analog_values();
void calculate_joystick_direction();

void print_slider();
void print_joystick();
ANALOG_DATA get_analog_data();

void button_interrupt_handler();