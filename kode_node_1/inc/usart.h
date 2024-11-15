#pragma once
#include <stdio.h>
#include "avr/interrupt.h"




void USART0_Init();
int USART0_Poll_Transmit(char data, FILE *file);
int USART0_Poll_Receive(FILE *file);

#ifdef UART_RX_ENABLED
void USART0_RX_IRQ_Handler(void);
void USART0_RX_IRQ_Enable();
int USART0_RX_DATA_Ready();
#endif
