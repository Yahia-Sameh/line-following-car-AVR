#ifndef COMMON_H
#define COMMON_H


#define F_CPU 16000000UL
#define BAUD_RATE 9600

#include <avr/interrupt.h>
extern volatile uint32_t millis_counter;
uint32_t millis(void);
void Timer_Init(void);

#endif