#include <avr/io.h>
#include "motor.h"
// === ENUMS for readability ===


// === Initialize PWM for any Timer ===
void PWM_Init(Timer_Select timer, PWM_Channel channel, PWM_Mode mode, uint16_t prescaler) {
	// Configure Data Direction Register (set output pin)
	if (timer == TIMER0 && channel == CHANNEL_A) DDRB |= (1 << PB3); // OC0A
	if (timer == TIMER0 && channel == CHANNEL_B) DDRD |= (1 << PD5); // OC0B
	if (timer == TIMER1 && channel == CHANNEL_A) DDRB |= (1 << PB1); // OC1A
	if (timer == TIMER1 && channel == CHANNEL_B) DDRB |= (1 << PB2); // OC1B
	if (timer == TIMER2 && channel == CHANNEL_A) DDRB |= (1 << PB3); // OC2A
	if (timer == TIMER2 && channel == CHANNEL_B) DDRD |= (1 << PD3); // OC2B

	switch (timer) {
		case TIMER0:
		if (mode == FAST_PWM) TCCR0A |= (1 << WGM00) | (1 << WGM01);
		else TCCR0A |= (1 << WGM00);  // Phase Correct
		if (channel == CHANNEL_A) TCCR0A |= (1 << COM0A1);
		if (channel == CHANNEL_B) TCCR0A |= (1 << COM0B1);
		// Prescaler
		switch (prescaler) {
			case 1: TCCR0B |= (1 << CS00); break;
			case 8: TCCR0B |= (1 << CS01); break;
			case 64: TCCR0B |= (1 << CS01)|(1<<CS00); break;
			case 256:TCCR0B |= (1 << CS02); break;
			case 1024:TCCR0B |= (1 << CS02)|(1<<CS00); break;
		}
		break;

		case TIMER1: // 16-bit
		if (mode == FAST_PWM) { TCCR1A |= (1 << WGM10); TCCR1B |= (1 << WGM12); }
		else TCCR1A |= (1 << WGM10);  // Phase Correct
		if (channel == CHANNEL_A) TCCR1A |= (1 << COM1A1);
		if (channel == CHANNEL_B) TCCR1A |= (1 << COM1B1);
		switch (prescaler) {
			case 1: TCCR1B |= (1 << CS10); break;
			case 8: TCCR1B |= (1 << CS11); break;
			case 64: TCCR1B |= (1 << CS11)|(1<<CS10); break;
			case 256:TCCR1B |= (1 << CS12); break;
			case 1024:TCCR1B |= (1 << CS12)|(1<<CS10); break;
		}
		break;

		case TIMER2:
		TCCR2A = 0; TCCR2B = 0;
		if (mode == FAST_PWM) TCCR2A |= (1 << WGM20) | (1 << WGM21);
		else TCCR2A |= (1 << WGM20);
		if (channel == CHANNEL_A) TCCR2A |= (1 << COM2A1);
		if (channel == CHANNEL_B) TCCR2A |= (1 << COM2B1);
		switch (prescaler) {
			case 1: TCCR2B |= (1 << CS20); break;
			case 8: TCCR2B |= (1 << CS21); break;
			case 32:TCCR2B |= (1 << CS21)|(1<<CS20); break;
			case 64:TCCR2B |= (1 << CS22); break;
			case 128:TCCR2B |= (1 << CS22)|(1<<CS20); break;
			case 256:TCCR2B |= (1 << CS22)|(1<<CS21); break;
			case 1024:TCCR2B |= (1 << CS22)|(1<<CS21)|(1<<CS20); break;
		}
		break;
	}
}

// === Set Duty Cycle ===
void PWM_SetDuty(Timer_Select timer, PWM_Channel channel, uint16_t duty) {
	switch (timer) {
		case TIMER0:
		if (channel == CHANNEL_A) OCR0A = duty;
		if (channel == CHANNEL_B) OCR0B = duty;
		break;
		case TIMER1: // 16-bit!
		if (channel == CHANNEL_A) OCR1A = duty;
		if (channel == CHANNEL_B) OCR1B = duty;
		break;
		case TIMER2:
		if (channel == CHANNEL_A) OCR2A = duty;
		if (channel == CHANNEL_B) OCR2B = duty;
		break;
	}
}
