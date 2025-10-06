#ifndef MOTOR_H
#define MOTOR_H

#include <avr/io.h>

typedef enum {
	TIMER0,
	TIMER1,
	TIMER2
} Timer_Select;

typedef enum {
	CHANNEL_A,
	CHANNEL_B
} PWM_Channel;

typedef enum {
	FAST_PWM,
	PHASE_CORRECT
} PWM_Mode;


void PWM_Init(Timer_Select timer, PWM_Channel channel, PWM_Mode mode, uint16_t prescaler);
void PWM_SetDuty(Timer_Select timer, PWM_Channel channel, uint16_t duty);

#endif // MOTOR_H
