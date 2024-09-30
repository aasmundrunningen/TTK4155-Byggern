#include "OLED_menu.h"
#include "OLED.h"
#include "config.h"
#include "avr/io.h"
#include "analog_input.h"
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <string.h>

OLED_menu_state_machine omsm = {.menu_level = 0, level0_sel = 0, level1_sel = 0,  .selected_line = 0};

void handle_button_press() {
    return;
}

void handle_joystick_movement() {
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
            omsm.level0 = omsm.selected_line;
            omsm.selected_line = 0;
        } else if (omsm.menu_level == 1) {
            omsm.menu_level += 1;
            omsm.level1 = omsm.selected_line;
            omsm.selected_line = 0;
        }   
        break;
    }
}

void draw_menu () {
    switch (omsm.menu_level) {
    case 0:
        for (int i = 0; i < 3; i++) {
            if (i == omsm.selected_line) {
                OLED_print_string(pgm_read_byte(&menu.menu_0[i]),strlen(pgm_read_byte(&menu.menu_0[i])), 20, 1+i*2, 1);
            } else {
                OLED_print_string(pgm_read_byte(&menu.menu_0[i]),strlen(pgm_read_byte(&menu.menu_0[i])), 20, 1+i*2, 0);
            }
        }
        break;
    case 1:
        for (int i = 0; i < 3; i++) {
            if (i == omsm.selected_line) {
                OLED_print_string(pgm_read_byte(&menu.menu_1[omsm.level0_sel][i]),strlen(pgm_read_byte(&menu.menu_1[omsm.level0_sel][i])), 20, 1+i*2, 1);
            } else {
                OLED_print_string(pgm_read_byte(&menu.menu_1[omsm.level0_sel][i]),strlen(pgm_read_byte(&menu.menu_1[omsm.level0_sel][i])), 20, 1+i*2, 0);
            }
        }
        break;
        case 2:
        for (int i = 0; i < 3; i++) {
            if (i == omsm.selected_line) {
                OLED_print_string(pgm_read_byte(&menu.menu_1[omsm.level0_sel][omsm.level1_sel][i]),strlen(pgm_read_byte(&menu.menu_1[omsm.level0_sel][omsm.level1_sel][i])), 20, 1+i*2, 1);
            } else {
                OLED_print_string(pgm_read_byte(&menu.menu_1[omsm.level0_sel][omsm.level1_sel][i]),strlen(pgm_read_byte(&menu.menu_1[omsm.level0_sel][omsm.level1_sel][i])), 20, 1+i*2, 0);
            }
        }
        break;
    }
}
