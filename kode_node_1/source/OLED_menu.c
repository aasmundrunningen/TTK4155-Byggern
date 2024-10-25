#include "OLED_menu.h"
#include "OLED.h"
#include "config.h"
#include "avr/io.h"
#include "analog_input.h"
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <string.h>

OLED_menu_state_machine omsm = {.menu_level = 0, .level0_sel = 0, .level1_sel = 0,  .selected_line = 0};


PROGMEM const char menu_0[3][16] = {"option1", "option2", "option3"};
PROGMEM const char menu_1[3][3][16] = {
    {"option11", "option12", "option13"},
    {"option21", "option22", "option23"},
    {"option31", "option32", "option33"}
};
PROGMEM  const char menu_2[3][3][3][16] = {
    {
        {"option111", "option112", "option113"},
        {"option121", "option122","option123"},
        {"option131", "option132", "option133"}
    },
    {
        {"option211", "option212", "option213"},
        {"option221", "option222", "option223"},
        {"option231", "option232", "option233"}
    },
    {
        {"option311", "option312", "option313"},
        {"option321", "option322", "option323"},
        {"option331", "option332", "option333"}
    }
};

void handle_button_press() {
    return;
}
JOYSTICK_DIRECTION previous_joystick_state = NEUTRAL;
void handle_joystick_movement() {
    update_analog_values();
    if(previous_joystick_state != NEUTRAL){
        previous_joystick_state = get_analog_data().joystick_direction;
    }else{
        previous_joystick_state = get_analog_data().joystick_direction;
        //whooops, good luck :)
        switch (get_analog_data().joystick_direction) {
            case NEUTRAL:
                break;
            case UP:
                if (omsm.selected_line == 0) {
                    omsm.selected_line = 2;
                } else {
                    omsm.selected_line -= 1;
                }
                break;
            case DOWN:
                if (omsm.selected_line == 2) {
                    omsm.selected_line = 0;
                } else {
                    omsm.selected_line += 1;
                }
                break;
            case LEFT:
                if (omsm.menu_level != 0) {
                    omsm.menu_level -= 1;
                    omsm.selected_line = 0;

                }
                break;
            case RIGHT:
                if (omsm.menu_level == 0) {
                    omsm.menu_level += 1;
                    omsm.level0_sel = omsm.selected_line;
                    omsm.selected_line = 0;
                } else if (omsm.menu_level == 1) {
                    omsm.menu_level += 1;
                }
                omsm.level1_sel = omsm.selected_line;
                omsm.selected_line = 0;
               
                break;
        }
    }
}

void OLED_menu_print_values(){
    printf("menu level:%d, level0_sel:%i, level1_sel:%i, selected_line:%i\n", omsm.menu_level, omsm.level0_sel, omsm.level1_sel, omsm.selected_line);
}

void draw_menu () {
    switch (omsm.menu_level) {
    case 0:
        for (int i = 0; i < 3; i++) {
            char str[16];
            for (int j = 0; j < 16; j ++) {
                char c = pgm_read_byte(&menu_0[i][j]);
                if(c == 0){
                    c = ' ';
                }
                str[j] = c;
            }
            OLED_print_string(str,16,1, 2+i, i==omsm.selected_line);
            
        }
        break;
    case 1:
        for (int i = 0; i < 3; i++) {
            char str[16];
            for (int j = 0; j < 16; j ++) {
                char c = pgm_read_byte(&menu_1[omsm.level0_sel][i][j]);
                if(c == 0){
                    c = ' ';
                }
                str[j] = c;
            }
            OLED_print_string(str,16,1, 2+i, i==omsm.selected_line);
        }
        break;
    case 2:
        for (int i = 0; i < 3; i++) {
            char str[16];
            for (int j = 0; j < 16; j ++) {
                char c = pgm_read_byte(&menu_2[omsm.level0_sel][omsm.level1_sel][i][j]);
                if(c == 0){
                    c = ' ';
                }
                str[j] = c;
            }
            OLED_print_string(str,16,1, 2+i, i==omsm.selected_line);
            
        }
        break;
    }
}
