#include "analog_input.h"
#include "config.h"
#include "can_controller.h"

void can_transmitt_joystick(){
    CAN_MESSAGE message;
    ANALOG_DATA data = get_analog_data();
    printf("data:");
    for(int i = 0; i < 5; i++){
        printf("%d, ", message.data[i]);
    }
    printf("\n");
    


    message.id = 0;
    message.length = 5;
    
    /*message.data[0] = (int8_t)data.joystick_x;
    message.data[1] = (int8_t)data.joystick_y;
    message.data[2] = data.joystick_direction;
    message.data[3] = (uint8_t)data.slider_1;
    message.data[4] = (uint8_t)data.slider_2;*/

    message.data[0] = 0;//(int8_t)data.joystick_x;
    message.data[1] = -128;//(int8_t)data.joystick_y;
    message.data[2] = 127;//data.joystick_direction;
    message.data[3] = 5;//(uint8_t)data.slider_1;
    message.data[4] = 1;

    can_controller_send(message, 0);
}