#pragma once
#include "sam3x8e.h"

#define set_bit(reg,bit )( reg |= ( 1 <<bit))
#define clear_bit( reg , bit )( reg &= ~(1 << bit ))
#define test_bit( reg , bit )( reg & ( 1 <<bit ))

#define clear_byte(reg, byte_number)(reg &= ~(0xFF<<(8*byte_number)))
#define set_byte(reg,byte_number,value)(reg |= value<<(8*byte_number))

#define CPU_FREQ 84000000
#define UART_BAUDRATE 9600