#pragma once

typedef enum {
    BIG,
    NORMAL,
    SMALL
} FONT_size;


void OLED_init();
void OLED_write_command(uint8_t command1, uint8_t command2 = 0xe3);
void OLED_write_screen();
void printf_oled(char[] input, FONT_size font_size);