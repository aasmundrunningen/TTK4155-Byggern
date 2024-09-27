#include "avr/io.h"
#include <stdio.h>
#include "config.h"
#include "util/delay.h"
#include "fonts.h"
#include "OLED.h"
#include "avr/pgmspace.h"


const uint8_t oled_init_sequence[] = {0xae, 0xa1, 0xda, 0x12, 0xc8, 0xa8, 0x3f, 0xd5, 0x80, 0x81, 0x50, 0xd9, 0x21, 0x20, 0x02, 0xdb, 0x30, 0xad, 0x00, 0xa4, 0xa6, 0xaf};
volatile uint8_t * OLED_command_register = (uint8_t*)OLED_start_command;
volatile uint8_t * OLED_data_register = (uint8_t*)OLED_start_data;

volatile uint8_t * screen_buffer = (uint8_t*)SCREEN_BUFFER;
uint8_t current_screen_buffer = 0;

void OLED_init() {
    for(int i = 0; i < sizeof(oled_init_sequence); i++){
        *OLED_command_register = oled_init_sequence[i];
    }

    for (int i = 0; i < 8192*2; i++) {
        screen_buffer[i] = 0;
    }


    //set point to 0
    *OLED_command_register = 0x00;
    *OLED_command_register = 0x10;
    
    //set page to 0
    *OLED_command_register = 0x22;
    *OLED_command_register = 0x00;
    for(int page = 0; page < 8; page ++){
        *OLED_command_register = 0x22;
        *OLED_command_register = page;
        for(int i = 0; i < 128; i++){
                *OLED_data_register = 0;
        }
    }

    printf("Finished OLED initialization\n");

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 8; j++)
        screen_buffer[i*8 + j] = pgm_read_byte(&font8[i][j]) ;
    }
}

void print_letter(char letter){
    for(int i = 0; i < 8; i++){
        *OLED_data_register = pgm_read_byte(&font8[(uint8_t)letter - 32][i]);
    }
}

void OLED_update_screen(){
    //set point to 0
    *OLED_command_register = 0x00;
    *OLED_command_register = 0x10;
    
    //set page to 0
    *OLED_command_register = 0x22;
    *OLED_command_register = 0x00;
    for(int page = 0; page < 8; page ++){
        *OLED_command_register = 0x22;
        *OLED_command_register = page;
        for(int i = 0; i < 128; i++){
                *OLED_data_register = screen_buffer[i + page*128 + current_screen_buffer*8192];
        }
    }
    
}

void printf_oled(char input[], uint8_t size, FONT_size font_size) {
    uint8_t current_char_index;
    switch (font_size) {
    case BIG:
        for (int i = 0; i < size; i++) {
            printf("-----\n");
            for(int j = 0; j < 8; j++){
                *OLED_data_register = font8[input[i]-32][j];
                printf("%i\n", input[i]);
                /**OLED_data_register = 0b00000000;    
                *OLED_data_register = 0b10000001;
                *OLED_data_register = 0b11111111;
                *OLED_data_register = 0b10000001;
                *OED_data_register = 0b00000000;*/
            }
        }
        break;
    case NORMAL:
        for (int i = 0; i < size; i++) {
            current_char_index =  input[i] - 32;
        }
        break;
    case SMALL:
        for (int i = 0; i < size; i++) {
            current_char_index = input[i] - 32;
        }
        break;
    }
}

void OLED_write_screen(){

}
 