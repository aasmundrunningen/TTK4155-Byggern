#pragma once
#include <avr/pgmspace.h>

/*static struct PROGMEM OLED_menu {
    char menu_0[][] = {"option1", "option2" "option3"};
    char menu_1[][][] = {{"option11", "option12", "option13"}, {"option21", "option22", "option23"}, {"option31", "option32", "option33"}};
    char menu_2[][][][] = {{{"option111", "option112", "option113"},
                         {"option121", "option122","option123"},
                          {"option131", "option132", "option133"}},
                                        {{"option211", "option212", "option213"}, 
                                        {"option221", "option222", "option223"},
                                         {"option231", "option232", "option233"}},
                                                    {{"option311", "option312", "option313"},
                                                     {"option321", "option322", "option323"},
                                                      {"option331", "option332", "option333"}}};
};
*/



typedef struct  {
    uint8_t menu_level;
    uint8_t level0_sel;
    uint8_t level1_sel;
    uint8_t selected_line;
} OLED_menu_state_machine;

void handle_button_press();
void handle_joystick_movement();
void draw_menu();
void OLED_menu_print_values();
