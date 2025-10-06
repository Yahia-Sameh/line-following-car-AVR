void MotorPins_Init(void) {
	DDRB |= (1 << PB0) | (1 << PB4) | (1 << PB2) | (1 << PB3);
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

void Car_SoftLeft(void) {
	LeftMotor_Backward();
	RightMotor_Forward();
	PWM_SetDuty(LEFT_TIMER, LEFT_CH, SPEED_TURN);      // slower left
	PWM_SetDuty(RIGHT_TIMER, RIGHT_CH, SPEED_NORMAL);  // normal right
}

void Car_SoftRight(void) {
	LeftMotor_Forward();
	RightMotor_Backward();
	PWM_SetDuty(LEFT_TIMER, LEFT_CH, SPEED_NORMAL);    // normal left
	PWM_SetDuty(RIGHT_TIMER, RIGHT_CH, SPEED_TURN);    // slower right
}

void Car_HardLeft(void) {
	LeftMotor_Backward();   // reverse left
	RightMotor_Forward();   // forward right
	PWM_SetDuty(LEFT_TIMER, LEFT_CH, SPEED_NORMAL); // Correction: Uses SPEED_NORMAL
	PWM_SetDuty(RIGHT_TIMER, RIGHT_CH, SPEED_NORMAL); // Correction: Uses SPEED_NORMAL
}

void Car_HardRight(void) {
	LeftMotor_Forward();    // forward left
	RightMotor_Backward();  // reverse right
	PWM_SetDuty(LEFT_TIMER, LEFT_CH, SPEED_NORMAL); // Correction: Uses SPEED_NORMAL
	PWM_SetDuty(RIGHT_TIMER, RIGHT_CH, SPEED_NORMAL); // Correction: Uses SPEED_NORMAL
}
void Car_Backward(void) {
	LeftMotor_Backward();
	RightMotor_Backward();
	PWM_SetDuty(LEFT_TIMER, LEFT_CH, SPEED_NORMAL);
	PWM_SetDuty(RIGHT_TIMER, RIGHT_CH, SPEED_NORMAL);
}
