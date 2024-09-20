#pragma once

#define F_CPU 4915000UL //CPU frequency in Hz
#define BAUDRATE_UART 9600 //baudrate in Hz

//bit opperations
#define set_bit(reg,bit )( reg |= ( 1 <<bit))
#define clear_bit( reg , bit )( reg &= ~(1 << bit ))
#define test_bit( reg , bit )( reg & ( 1 <<bit ))
//#define loop_until_bit_is_set(reg,bit) while(!test_bit (reg , bit))
//#define loop_until_bit_is_clear(reg,bit) while(test_bit(reg,bit))

#define WRITEBACK_MODE 1 // 1 = instant writeback // 

#define UART_CALLBACK //sens all characters back to the UART terminal
#define JOYSTICK_CALIBRATION
#define JOYSTICK_deadzone 10

#define ADC_address 0x1410
#define OLED_start_command 0x1000
#define OLED_command_register_size 0x1FF
#define OLED_start_data 0x1200
#define OLED_data_register_size 0x1FF