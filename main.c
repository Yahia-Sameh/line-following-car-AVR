#include "common.h"
#include <avr/io.h>
#include <util/delay.h>
#include "motor.h"
#include "IR.h"
#include "uart.h"   // already in your project
#include "Mcon.h"

// Left motor direction
#define LEFT_IN1   PB0
#define LEFT_IN2   PB4
// Right motor direction
#define RIGHT_IN3  PB2
#define RIGHT_IN4  PB3

// ===== Speed Settings =====
#define SPEED_STOP    0
#define SPEED_NORMAL  255
#define SPEED_TURN    180 // Correction: Changed to SPEED_NORMAL for pivot turns

// ===== Motor Mapping =====
#define LEFT_TIMER   TIMER0
#define LEFT_CH      CHANNEL_B   // PD3 (OC0B)
#define RIGHT_TIMER  TIMER2
#define RIGHT_CH     CHANNEL_B   // PD5 (OC2B)




// ===== Main Program =====
/*
int main(void) {
	MotorPins_Init();
	IR_Init();
	UART_Init();   // UART for Bluetooth

	PWM_Init(LEFT_TIMER, LEFT_CH, FAST_PWM, 1);
	PWM_Init(RIGHT_TIMER, RIGHT_CH, FAST_PWM, 1);

	Car_Stop();
	uint8_t sensors=0;
	uint8_t started = 0;   // start flag
	uint8_t cmd = 'P';
	while (1) 
	{
		if(!(UCSR0A & (1 << RXC0)))
		{
			if(started)cmd = 'A';
			else cmd = 'P';
		}
		else cmd = UDR0;
		if (cmd == 'A')
		{
			started = 1;               // start robot
		}
		else if(cmd=='P')
		{
			started = 0;
			UART_Transmit(1);
		}
		if(started==0)
		{
			switch (cmd)
			{
				case 'F': Car_Forward(); break;
				case 'B': Car_Backward(); break;
				case 'L': Car_HardLeft(); break;
				case 'R': Car_HardRight(); break;
				case 'S': Car_Stop(); break;
				default: Car_Stop(); break;
			}
		}
		else if(started==1)
		{
			sensors= ~IR_Read();
			if(sensors==255)
			{
				Car_Stop();
				_delay_ms(2500);
			}
			else if ((sensors&(1<<0))==(1<<0))
			{
				Car_HardLeft();
				//_delay_ms(50);
			}
			else if ((sensors&(1<<1))==(1<<1))
			{
				Car_SoftLeft();
				//_delay_ms(50);
			}
			else if ((sensors&(1<<4))==(1<<4))
			{
				Car_HardRight();
				//_delay_ms(50);
			}
			else if ((sensors&(1<<3))==(1<<3))
			{
				Car_SoftRight();
				//_delay_ms(50);
			}
			else if((sensors & (1<<2)) == (1<<2))
			{
				Car_Forward();
			}
		}
	}
}
*/


int main(void) {
	// Init
	UART_Init();
	MotorPins_Init();
	IR_Init();

	// Init PWM channels
	PWM_Init(LEFT_TIMER, LEFT_CH, FAST_PWM, 64);
	PWM_Init(RIGHT_TIMER, RIGHT_CH, FAST_PWM, 64);

	Car_Stop();
	uint8_t sensors=0;
	while (1) {
		uint8_t cmd = UART_Receive();

		switch (cmd) {
			case 'F': Car_Forward(); break;
			case 'B': Car_Backward(); break;
			case 'L': Car_HardLeft(); break;
			case 'R': Car_HardRight(); break;
			case 'S': Car_Stop(); break;
			case 'A':
			{
				while(UDR0!='P')
				{
					sensors= ~IR_Read();
					if(sensors==255)
					{
						Car_Stop();
						_delay_ms(2500);
					}
					else if ((sensors&(1<<0))==(1<<0))
					{
						Car_HardLeft();
						//_delay_ms(50);
					}
					else if ((sensors&(1<<1))==(1<<1))
					{
						Car_SoftLeft();
						//_delay_ms(50);
					}
					else if ((sensors&(1<<4))==(1<<4))
					{
						Car_HardRight();
						//_delay_ms(50);
					}
					else if ((sensors&(1<<3))==(1<<3))
					{
						Car_SoftRight();
						//_delay_ms(50);
					}
					else if((sensors & (1<<2)) == (1<<2))
					{
						Car_Forward();
					}
				}
			}
			default:  Car_Stop(); break;
		}
	}
}