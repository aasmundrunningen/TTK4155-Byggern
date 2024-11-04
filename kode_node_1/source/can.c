#include "analog_input.h"
#include "config.h"
#include "can_controller.h"
#include <string.h>

extern ANALOG_DATA analog_data[];

void can_transmitt_joystick(){
    CAN_MESSAGE message;
    /*Can_Data_Interface data;
    data.data = get_analog_data();
    ANALOG_DATA t = get_analog_data();
    printf("x:%d\n", t.joystick_x);*/
    message.id = 0;
    message.length = 8;
    memcpy(message.data, analog_data, 8);
    can_controller_send(message, 0);
}