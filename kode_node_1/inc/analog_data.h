#pragma once

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
    uint8_t joystick_offsett_x;
    uint8_t joystick_offsett_y;
    int8_t joystick_x;
    int8_t joystick_y;
    uint8_t slider_1;
    uint8_t slider_2;
    uint8_t activate_solenoid;
    JOYSTICK_DIRECTION joystick_direction;
} ANALOG_DATA;


typedef union{
    ANALOG_DATA data;
    uint8_t data_unformated[8];
} Can_Data_Interface;