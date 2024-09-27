#pragma once

typedef enum {
    BIG,
    NORMAL,
    SMALL
} FONT_size;


void OLED_init();
void OLED_write_screen();
void print_letter(char letter);
void printf_oled(char input[], uint8_t size, FONT_size font_size);
void OLED_update_screen();