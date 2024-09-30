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
#define JOYSTICK_deadzone 30
#define JOYSTICK_CALIBRATION_SAMPLES 1


#define ADC_address 0x1410
#define OLED_start_command 0x1000
#define OLED_command_register_size 0x1FF
#define OLED_start_data 0x1200
#define OLED_data_register_size 0x1FF // 512 bytes = half of what is needed for the full oled (1024 bytes). Need to loop twice. (reset counter)


#define SRAM_START_ADDRESS 0x1800
#define SCREEN_BUFFER 0x1800
#define SCREEN_BUFFER_size 0x4000