#include "avr/io.h"
#include <stdio.h>
#include "util/delay.h"
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
#define CAN_CONTROLLER_READ_TX_BUFFER 0x90


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



#define TXB0_BASE     0x30
#define TXB1_BASE     0x40
#define TXB2_BASE     0x50
#define RXB0_BASE     0x60
#define RXB1_BASE     0x70

#define CTRL  0x00
#define SIDH  0x01
#define SIDL  0x02
#define EID8  0x03
#define EID0  0x04
#define DLC   0x05
#define DATA0 0x06


CAN_MESSAGE recive_buffer[2];
uint8_t recive_flag[2];

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

    //can_controller_write(CANINTE, 0b00100011); //enables interrupt on error and recive buffer 0 and 1
    can_controller_write(CANINTE, 0b00000011); //enables interrupt on error and recive buffer 0 and 1


    can_controller_write(RXB0_BASE+CTRL, 0b011000100); //RXB0CTRL, turn of mask and enable rollover to buffer 0
    can_controller_write(RXB1_BASE+CTRL, 0b011000000); //RXB1CTRL, turn of mask

    can_controller_write(BFCTRL, 0b00001111); // Turn on dpin functions on RX

    can_controller_write(TXB0_BASE+SIDL, 0);
    can_controller_write(TXB1_BASE+SIDL, 0);
    can_controller_write(TXB2_BASE+SIDL, 0);

    #ifdef CAN_LOOPBACK
        can_controller_write(0x0f, 0x40); //set status register in loopback
    #else 
        can_controller_write(0x0f, 0x00); //set status register in normal
    #endif

    can_controller_recive_IRQ_enable();

}

void can_controller_send(CAN_MESSAGE _message, uint8_t buffer) {
    if (_message.length > 8) {
        printf("Error: Tried to send a CAN-message longer than 8 bytes");
        return;
    }
    can_controller_write(TXB0_BASE+DLC+buffer*16, _message.length); // set the length of the message to be sent

    
    can_controller_write(TXB0_BASE+SIDH+buffer*16, _message.id);

    for (int i = 0; i < _message.length; i++) {
        uint8_t address = TXB0_BASE+DATA0+16*buffer+i;
        can_controller_write(address, _message.data[i]);
    }

    can_controller_rts(buffer);
}

void can_controller_IRQ_handler(){
    //uint8_t status = can_controller_read_status();
    heart_beat();
    recive_buffer[0] = can_controller_read_rx_buffer(0);
    recive_buffer[1] = can_controller_read_rx_buffer(1);
    can_controller_write(CANINTF, 0); //clears whole interrupt register
    /*if(status & 0x1){
        //recive buffer 0
        recive_flag[0]=1;
        recive_buffer[0] = can_controller_read_rx_buffer(0);
        can_controller_bit_modify(CANINTF, 1,0);
    }
    if(status & 0x2){
        recive_flag[1]=1;
        recive_buffer[1] = can_controller_read_rx_buffer(1);
        can_controller_bit_modify(CANINTF, 2,0);
    }
    else{
        can_controller_write(CANINTF, 0); //clears whole interrupt register
    }*/

}

void can_controller_recive_IRQ_enable(){
    clear_bit(DDRD,PIN2); //set pin as input
    //set interrupt on falling edge of int0
    set_bit(MCUCR,ISC01);
    clear_bit(MCUCR,ISC00);

    //enables interrupt on int0
    set_bit(GICR,INT0); 
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


CAN_MESSAGE can_controller_read_rx_buffer(uint8_t _buffer){
    uint8_t base_address = RXB0_BASE+_buffer*16;
    CAN_MESSAGE message;
    message.id = can_controller_read(base_address+SIDH);
    message.length = can_controller_read(base_address+DLC);
    for(int i = 0; i < 8; i++){
        if(i < message.length){
            message.data[i] = can_controller_read(base_address+DATA0+i);
        }else{
            message.data[i] = 0;
        }

    }
    return message;
}

void can_controller_write(uint8_t _address, uint8_t _data){
    char data[] = {CAN_CONTROLLER_WRITE, _address, _data};
    spi_transmitt_recive(data, 3);
}

void can_controller_bit_modify(uint8_t _address, uint8_t _mask, uint8_t _data){
    char data[] = {CAN_CONTROLLER_BIT_MODIFY, _address, _mask, _data};
    spi_transmitt_recive(data, 4);
}

void can_controller_rts(uint8_t _buffer){
    char data[] = {CAN_CONTROLLER_RTS};
    data[0] = data[0] | (1<<_buffer);
    spi_transmitt_recive(data, 1);
}


/*
CAN_MESSAGE message_rx;
CAN_MESSAGE message_tx;

uint8_t x[] = {1,0,0};
void can_controller_test(){   
    message_tx.id = 24;
    message_tx.length = 8;
    strcpy(message_tx.data, "hei du!");

    can_controller_send(message_tx, 0);
    printf("--CAN test--\n");
    printf("id:%d, length:%d, data0:%c\n",
        can_controller_read(TXB0_BASE+SIDH),
        can_controller_read(TXB0_BASE+DLC),
        can_controller_read(TXB0_BASE+DATA0));
    

    _delay_ms(500);
    printf("recived: flag:%d data:%s\n", recive_flag[0], recive_buffer[0].data);
    printf("--CAN test finished--\n");
    
    
    /*message_rx = can_controller_read_rx_buffer(0);
    printf("recived: id:%d, length:%d, data:%s\n",message_rx.id, message_rx.length, message_rx.data);
    
}
*/