#include "avr/io.h"
#include <stdio.h>
#include "config.h"
#include "util/delay.h"

#include "OLED.h"
uint8_t offset = [0xae, 0xa1, 0xda, 0x12, 0xc8, 0xa8, 0x3f, 0xd5, 0x80, 0x81, 0x50, 0xd9, 0x21, 0x20, 0x02, 0xdb, 0x30, 0xad, 0x00, 0xa4, 0xa6, 0xaf];

void OLED_write_command(uint8_t command1, uint8_t command2 = 0xe3){
    uint8_t * oled_command_p = (uint8_t*)OLED_start_command; 
    *(oled_command_p + command1) = (OLED_start_command + command2);
}

void OLED_init() {

    int size_offset = sizeof(offset);
    for(int i = 0; i < size_offset; i+=2){
        OLED_write_command(offset[i], offset[i+1]);
    }


}

void printf_oled(char[] input, FONT_size font_size) {
    uint8_t current_char_index;
    switch (font_size) {
    case BIG:
        for (i = 0; i < sizeof(input); i++) {
            current_char_index =  input[i] - 32; // Get the correct index in fonts datastructure

        }
        break;
    case NORMAL:
        for (i = 0; i < sizeof(input); i++) {
            current_char_index =  input[i] - 32;
        }
        break;
    case SMALL:
        for (i = 0; i < sizeof(input); i++) {
            current_char_index = input[i] - 32
        }
        break;
    }
}

void OLED_write_screen(){

}
 