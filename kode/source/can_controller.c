#include "config.h"
#include "can_controller.h"
#include "spi.h"
#include "avr/io.h"
#include <stdio.h>

#define CAN_CONTROLLER_WRITE 0x02
#define CAN_CONTROLLER_READ 0x03
#define CAN_CONTROLLER_RESET 0xC0
#define CAN_CONTROLLER_READ_STATUS 0xA0
#define CAN_CONTROLLER_RX_STATUS 0xB0
#define CAN_CONTROLLER_BIT_MODIFY 0x05
#define CAN_CONTROLLER_RTS 0x80 //this is the mask, add lower tre bits for selecting buffer

void can_controller_init(){

}

void can_controller_write(uint8_t address, uint8_t data){
    char data[3] = {CAN_CONTROLLER_WRITE, address, data};
    spi_transmitt_recive(data, 3);
}

uint8_t can_controller_read(uint8_t address){
    char data[3] = {CAN_CONTROLLER_READ, address, 0x00};
    spi_transmitt_recive(data, 3);
    return data[2];
}

