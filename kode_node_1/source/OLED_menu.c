#include "OLED_menu.h"
#include "OLED.h"
#include "config.h"
#include "avr/io.h"
#include "analog_input.h"
#include "can.h"
#include "can_controller.h"
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <string.h>


OLED_menu_state_machine omsm = {.menu_level = 0, .level0_sel = 0, .level1_sel = 0,  .selected_line = 0, .playing = 0};

PROGMEM const char menu_0[3][16] = {"play game?", "i am boring", "fun facts"};
PROGMEM const char menu_1[3][3][16] = {
    {"yes?", "no", "i hate kids"},
    {"poop", "poop", "poooop"},
    {"Random", "Animals", "Space"}
};
PROGMEM  const char menu_2[3][3][3][16] = {
    {
        {"yes!", "prank", "yank!"},
        {"no", "no","noooooooo"},
        {"children", "hate you", "even more."}
    },
    {
        {"option211", "option212", "option213"},
        {"option221", "option222", "option223"},
        {"pop", ":):):):):", ":):):):):)"}
    },
    {
        {"toilet paper", "roll is 25m", "long."},
        {"slugs have", "four noses.", "oh no!"},
        {"The moon", "is lemon", "shaped"}
    }
};

void handle_button_press() {
    return;
}
JOYSTICK_DIRECTION previous_joystick_state = NEUTRAL;
void handle_joystick_movement() {
    update_analog_values();
    if (omsm.playing == 1) {
        return;
    }
    if(previous_joystick_state != NEUTRAL){
        previous_joystick_state = get_analog_data().joystick_direction;
    }else{
        previous_joystick_state = get_analog_data().joystick_direction;
        //whooops, good luck :)can_transmit
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
                if (omsm.level0_sel == 0 && omsm.level1_sel == 0 && omsm.menu_level == 2) {
                    omsm.playing = 1;
                    break;
                }
                if (omsm.menu_level == 2) {
                    break;
                }
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
    if (omsm.playing == 0) {
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
                    if(c == 0){        switch (omsm.menu_level) {
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
    } else {
        //OLED_print_string("6",1, 7, 4, 0);
        OLED_print_string((char)(can_controller_read_rx_buffer(0).data[0]), 1, 7, 4, 0);
    }
}
