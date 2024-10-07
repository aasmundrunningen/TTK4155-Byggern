#include "avr/io.h"
#include <stdio.h>
#include "config.h"
#include "can_controller.h"
#include "spi.h"


#define CAN_CONTROLLER_WRITE 0x02
#define CAN_CONTROLLER_READ 0x03
#define CAN_CONTROLLER_RESET 0xC0
#define CAN_CONTROLLER_READ_STATUS 0xA0
#define CAN_CONTROLLER_RX_STATUS 0xB0
#define CAN_CONTROLLER_BIT_MODIFY 0x05
#define CAN_CONTROLLER_RTS 0x80 //this is the mask, add lower tre bits for selecting buffer
#define CAN_CONTROLLER_LOAD_TX_BUFFER 0x40
#define CAN_CONTROLLER_READ_TX_BUFFER 


#define BFCTRL       0x0C
#define TXRTSCTRL    0x0D
#define CANSTAT      0x0E
#define CANCTRL      0x0F
#define TEC          0x1C
#define REC          0x1D
#define CNF3         0x28
#define CNF2         0x29
#define CNF1         0x2A
#define CANINTE      0x2B
#define CANINTF      0x2C
#define EFLG         0x2D
#define TXB0CTRL     0x30
#define TXB1CTRL     0x40
#define TXB2CTRL     0x50
#define RXB0CTRL     0x60
#define RXB1CTRL     0x70



void can_controller_init(){
    spi_init();

    can_controller_reset();
    _delay_ms(1); //lets the controller reset


    /*
        BRP (baud rate prescaler) = 0
        => TQ = 2/f_osc = 2/2.45MHz = 820nS
        =>T_can = Bit_time * TQ = 6*82uS = 4.9uS
        =>f_can = 1/T_can = 200kHz
        Bit time = 6TQ
            syncseg = 1TQ
            propseg = 1TQ
            PS1 = 2TQ
            PS2 = 2TQ

    */

    /*
    Register: CNF1
    BRP = 0, no prescaler
    SJW = 0, syncronisation max is 1TQ
    */
    can_controller_write(CNF1, 0);

    /*
    Register: CNF2
    BIT 7: 1, PS2 length determined by CNF3
    BIT 6: 0, bus line sampled at one point
    BIT 5-3: 1, gives PS1 at 1 bit
    BIT 2-0: 0, gives Propegation segment length of 1bit
    */
    can_controller_write(CNF2, 0b10001000);

    /*
    Register: CNF3
    Bit7: 0, no clockout
    Bit6: 0, no wake-up filter
    Bit6-3: not implemented
    Bit 2-0: 1, PS2=2TQ
    */
    can_controller_write(CNF3, 1);

    can_controller_write(CANINTE, 0b00100011); //enables interrupt on error and recive buffer 0 and 1

    can_controller_write(RXB0CTRL, 0b011001000); //RXB0CTRL, turn of mask and enable rollover to buffer 0
    can_controller_write(RXB1CTRL, 0b011000000); //RXB1CTRL, turn of mask

    #ifdef CAN_LOOPBACK
        can_controller_write(0x0f, 0x40); //set status register in loopback
    #else 
        can_controller_write(0x0f, 0x00); //set status register in normal
    #endif

}

uint8_t can_controller_read(uint8_t _address){
    char data[] = {CAN_CONTROLLER_READ, _address, 0x00};
    spi_transmitt_recive(data, 3);
    return data[2];
}

void can_controller_reset(){
    char data[] = {CAN_CONTROLLER_RESET};
    spi_transmitt_recive(data, 1);
}

//returns 1 if error, all other values are correct status
uint8_t can_controller_read_status(){
    char data[] = {CAN_CONTROLLER_READ_STATUS, 3, 4};
    spi_transmitt_recive(data,3);
    if(data[1] != data[2]){
        #ifdef ERROR_PRINT
            printf("ERROR: can_controller_read_status, mismatch in data");
        #endif
        return 1;
    }
    return (uint8_t)data[1];
}

void can_controller_load_tx_buffer(uint16_t _id, char _data[], uint8_t _length) {
    char spi_data[] = {}
    spi_transmitt_recive
}

void can_controller_write(uint8_t _address, uint8_t _data){
    char data[] = {CAN_CONTROLLER_WRITE, _address, _data};
    spi_transmitt_recive(data, 3);
}

void can_controller_bit_modify(uint8_t _address, uint8_t _mask, uint8_t _data){
    char data[] = {CAN_CONTROLLER_BIT_MODIFY, _address, _mask, _data};
    spi_transmitt_recive(data, 4);
}

void can_controller_rts(uint8_t _id){
    char data[] = {CAN_CONTROLLER_RTS | _id};
    spi_transmitt_recive(data, 1);
}


