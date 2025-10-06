#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <util/delay.h>


void UART_Init(void);
void UART_Transmit(uint8_t data);
uint8_t UART_Receive(void);
void UART_SendString(const char* str);

#endif