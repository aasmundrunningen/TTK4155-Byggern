#include "config.h"
#include "avr/io.h"
#include "spi.h"
#include <stdio.h>


#define DDR_SPI DDRB
#define SS_PORT PORTB
#define SS_PIN PB4
#define MOSI_PIN PIN5
#define MISO_PIN PIN6
#define SCK_PIN PIN7


void spi_init(){
    //set input and output pins
    set_bit(DDR_SPI, SCK_PIN);
    set_bit(DDR_SPI, MOSI_PIN);
    set_bit(DDR_SPI, SS_PIN);
    clear_bit(DDR_SPI, MISO_PIN);
    
    
    set_bit(SPCR, MSTR); //set master
    
    clear_bit(SPCR, SPR0); //clock rate as f_osc/16
    clear_bit(SPCR, SPR1); //clock rate as f_osc/16

    set_bit(SS_PORT, SS_PIN); //dissable slave select
    
    set_bit(SPCR, SPE); //spi enable

}

void spi_transmitt_recive(char data[], uint8_t length){
    clear_bit(SS_PORT, SS_PIN); //enable slave select
    for(int i = 0; i < length; i++){
        SPDR = data[i];

            //wait for transmittion complete
            while(!(SPSR &  (1<<SPIF))){
        
        }
        data[i] = SPDR;
    }
    
    set_bit(SS_PORT, SS_PIN); //dissable slave select
}