#include "analog_input.h"
#include "config.h"
#include "can_controller.h"

void can_transmitt_joystick(){
    update_analog_values();
    CAN_MESSAGE message;
    ANALOG_DATA data = get_analog_data();
    printf("data: x: %d, y: %d, dir: %d, s1: %u, s2: %u\n",
        message.data[0],
        message.data[1],
        message.data[2],
        message.data[3],
        message.data[4]
        );
    
    message.id = 0;
    message.length = 4;
    
    message.data[0] = (int8_t)data.joystick_x;
    message.data[1] = (int8_t)data.joystick_y;
    message.data[2] = data.joystick_direction;
    message.data[3] = (uint8_t)data.slider_1;
    message.data[4] = (uint8_t)data.slider_2;
    can_controller_send(message, 0);
}