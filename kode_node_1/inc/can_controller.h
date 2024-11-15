#pragma once

typedef enum {
    MESSAGE_1,
    MESSAGE_2,
    MESSAGE_3
} CAN_MESSAGE_IDS;

typedef struct {
    uint8_t id;
    uint8_t length;
    char data[8];
} CAN_MESSAGE;

void can_controller_init(); //not finished
void can_controller_reset();
void can_controller_rts(uint8_t _buffer);

uint8_t can_controller_read(uint8_t _address);  //working
uint8_t can_controller_read_status(); //returns 1 if error, all other values are correct status, unkown
void can_controller_write(uint8_t _address, uint8_t _data); //working
void can_controller_bit_modify(uint8_t _address, uint8_t _mask, uint8_t _data);

void can_controller_send(CAN_MESSAGE _message, uint8_t _buffer);
CAN_MESSAGE can_controller_read_rx_buffer(uint8_t _buffer);


//void can_controller_test();