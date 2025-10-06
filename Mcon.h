#ifndef MCON_H
#define MCON_H

#include <avr/io.h>

// ===== Speed Settings =====
#define SPEED_STOP    0
#define SPEED_NORMAL  255
#define SPEED_TURN    0

// ===== Motor Mapping =====
#define LEFT_TIMER   TIMER0
#define LEFT_CH      CHANNEL_B   // PD3 (OC0B)
#define RIGHT_TIMER  TIMER2
#define RIGHT_CH     CHANNEL_B   // PD5 (OC2B)

// ===== API =====
void MotorPins_Init(void);

// Motor helpers
void LeftMotor_Forward(void);
void LeftMotor_Backward(void);
void RightMotor_Forward(void);
void RightMotor_Backward(void);

// Movement control
void Car_Stop(void);
void Car_Forward(void);
void Car_SoftLeft(void);
void Car_SoftRight(void);
void Car_HardLeft(void);
void Car_HardRight(void);

#endif // MCON_H
