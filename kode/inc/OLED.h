#pragma once

typedef enum {
    BIG,
    NORMAL,
    SMALL
} FONT_size;


void OLED_init();
void OLED_write_screen();
void OLED_print_letter(char _letter, uint8_t _coloum, uint8_t _page);
void OLED_print_line(uint8_t _start_coloum, uint8_t row, uint8_t _length, uint8_t _dashed);
int OLED_print_string(char[] _string, uint8_t _coloum, uint8_t _page); //returns 0 if OK returns 1 if out of boarder writing



void OLED_print_byte(uint8_t _value, uint8_t _page, uint8_t _coloum);



void OLED_update_screen();