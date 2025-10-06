#include "common.h"
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "motor.h"

#define BAUD_RATE 9600

// ===== Pin Definitions =====
// Left motor direction
#define LEFT_IN1   PB0
#define LEFT_IN2   PB1
// Right motor direction
#define RIGHT_IN3  PB2
#define RIGHT_IN4  PB3

// ===== Speed Settings (0–255 for 8-bit PWM) =====
#define SPEED_STOP    0
#define SPEED_NORMAL  255
#define SPEED_TURN    100

// ===== Motor Mapping =====
#define LEFT_TIMER   TIMER0
#define LEFT_CH      CHANNEL_B   // PD3 (OC2B)
#define RIGHT_TIMER  TIMER2
#define RIGHT_CH     CHANNEL_B   // PD5 (OC0B)

// ===== Helpers =====
void MotorPins_Init(void) {
	// Set direction pins as output
	DDRB |= (1 << LEFT_IN1) | (1 << LEFT_IN2) | (1 << RIGHT_IN3) | (1 << RIGHT_IN4);
}

void LeftMotor_Forward(void) {
	PORTB |= (1 << LEFT_IN1);
	PORTB &= ~(1 << LEFT_IN2);
}

void LeftMotor_Backward(void) {
	PORTB &= ~(1 << LEFT_IN1);
	PORTB |= (1 << LEFT_IN2);
}

void RightMotor_Forward(void) {
	PORTB |= (1 << RIGHT_IN3);
	PORTB &= ~(1 << RIGHT_IN4);
}

void RightMotor_Backward(void) {
	PORTB &= ~(1 << RIGHT_IN3);
	PORTB |= (1 << RIGHT_IN4);
}

void Car_Stop(void) {
	PWM_SetDuty(LEFT_TIMER, LEFT_CH, SPEED_STOP);
	PWM_SetDuty(RIGHT_TIMER, RIGHT_CH, SPEED_STOP);
}

// ===== Movements =====
void Car_Forward(void) {
	LeftMotor_Forward();
	RightMotor_Forward();
	PWM_SetDuty(LEFT_TIMER, LEFT_CH, SPEED_NORMAL);
	PWM_SetDuty(RIGHT_TIMER, RIGHT_CH, SPEED_NORMAL);
}

void Car_Backward(void) {
	LeftMotor_Backward();
	RightMotor_Backward();
	PWM_SetDuty(LEFT_TIMER, LEFT_CH, SPEED_NORMAL);
	PWM_SetDuty(RIGHT_TIMER, RIGHT_CH, SPEED_NORMAL);
}

void Car_Left(void) {
	LeftMotor_Forward();
	RightMotor_Forward();
	PWM_SetDuty(LEFT_TIMER, LEFT_CH, SPEED_TURN );  // slower left
	PWM_SetDuty(RIGHT_TIMER, RIGHT_CH, SPEED_NORMAL);      // faster right
}

void Car_Right(void) {
	LeftMotor_Forward();
	RightMotor_Forward();
	PWM_SetDuty(LEFT_TIMER, LEFT_CH, SPEED_NORMAL);        // faster left
	PWM_SetDuty(RIGHT_TIMER, RIGHT_CH, SPEED_TURN);// slower right
}

int main(void) {
	// Init
	UART_Init();
	MotorPins_Init();

	// Init PWM channels
	PWM_Init(LEFT_TIMER, LEFT_CH, FAST_PWM, 64);
	PWM_Init(RIGHT_TIMER, RIGHT_CH, FAST_PWM, 64);

	Car_Stop();

	while (1) {
		uint8_t cmd = UART_Receive();

		switch (cmd) {
			case 'F': Car_Forward(); break;
			case 'B': Car_Backward(); break;
			case 'L': Car_Left(); break;
			case 'R': Car_Right(); break;
			case 'S': Car_Stop(); break;
			default:  Car_Stop(); break;
		}
	}
}
