#pragma once
#include <stdio.h>

void USART0_Init();
//void USART0_Transmit( unsigned char data ); 
//unsigned char USART0_Receive( void);

int USART0_Poll_Transmit(char data, FILE *file);
int USART0_Poll_Receive(FILE *file);