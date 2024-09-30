#include "avr/io.h"
#include <stdio.h>
#include "config.h"
#include "util/delay.h"
#include "fonts.h"
#include "OLED.h"
#include "avr/pgmspace.h"


const uint8_t oled_init_sequence[] = {0xae, 0xa1, 0xda, 0x12, 0xc8, 0xa8, 0x3f, 0xd5, 0x80, 0x81, 0x50, 0xd9, 0x21, 0x20, 0x02, 0xdb, 0x30, 0xad, 0x00, 0xa4, 0xa6, 0x40, 0xaf};
volatile uint8_t * OLED_command_register = (uint8_t*)OLED_start_command;
volatile uint8_t * OLED_data_register = (uint8_t*)OLED_start_data;

volatile uint8_t * screen_buffer = (uint8_t*)SCREEN_BUFFER;

void OLED_init() {
    for(int i = 0; i < sizeof(oled_init_sequence); i++){
        *OLED_command_register = oled_init_sequence[i];
    }
    OLED_clear_screen();
    OLED_print_string("BOOTING", 7, 4, 4, 0);
    OLED_update_screen();
    _delay_ms(2000);
    OLED_clear_screen();
    OLED_update_screen();
    printf("Finished OLED initialization\n");
}

void OLED_print_letter(char _letter, uint8_t _coloum, uint8_t _page, uint8_t _inverted){
    for(int i = 0; i < 8; i++){
        if(_inverted){
            screen_buffer[i + _coloum*8 + _page*128] = ~pgm_read_byte(&font8[(uint8_t)_letter - 32][i]);    
        }
        else{
            screen_buffer[i + _coloum*8 + _page*128] = pgm_read_byte(&font8[(uint8_t)_letter - 32][i]);
        }
    }
}

void OLED_print_line(uint8_t _start_coloum, uint8_t _row, uint8_t _length, uint8_t _dashed){
    for(int i = 0; i < _length; i++){
        screen_buffer[_start_coloum+i + _row/8*128] |= (!_dashed | i%2) << _row%8;
    }
}

int OLED_print_string(char _string[], uint8_t _string_size, uint8_t _coloum, uint8_t _page, uint8_t _inverted){
    int error = 0;
    
    for(int i = 0; i < _string_size; i++){
        if(_string[i] == '\n'){
            _page ++;
            _coloum = 0;
        }
        else{
            if(_coloum > 15 || _page > 7){
                error = 1;
            }
            else{
                OLED_print_letter(_string[i], _coloum, _page, _inverted);
                _coloum ++;
            }
        }

    }
    return error;
}

void OLED_print_byte(uint8_t _value, uint8_t _page, uint8_t _coloum){
    screen_buffer[_coloum + _page*128] = _value;
}

void OLED_clear_screen(){
    for (int i = 0; i < 8192; i++) {
        screen_buffer[i] = 0;
    }
}

void OLED_update_screen(){
    //set point to 0
    *OLED_command_register = 0x00;
    *OLED_command_register = 0x10;
    
    for(int page = 0; page < 8; page ++){
        *OLED_command_register = 0xB0 + page; //update page
        for(int i = 0; i < 128; i++){
                *OLED_data_register = screen_buffer[i + page*128];
        }
    }
    
}

 