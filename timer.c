#include "common.h"
#include <avr/interrupt.h>

volatile uint32_t millis_counter = 0;

ISR(TIMER0_COMPA_vect) {
    millis_counter++;  // Increment every 1 ms (250 counts)
}

void Timer_Init(int x) {
	switch(x){
		case 1:
    TCCR0A = (1 << WGM01);  // CTC mode (clear timer on compare match)
    TCCR0B = (1 << CS01) | (1 << CS00);  // Prescaler 64
    OCR0A = 250 - 1;  // Compare match at 250 (0 to 249)
    TIMSK0 |= (1 << OCIE0A);  // Enable Compare Match A interrupt
	break;
	case 2:
	// Fast PWM Mode (WGM01=1, WGM00=1)
	TCCR0A |= (1 << WGM00) | (1 << WGM01);

	// Non-inverting mode on OC0A
	TCCR0A |= (1 << COM0A1);
	TCCR0A &= ~(1 << COM0A0);

	// Prescaler = 64 (gives ~976 Hz PWM at 16 MHz clock)
	TCCR0B |= (1 << CS01) | (1 << CS00);
	break;
	}
}

uint32_t millis(void) {
    uint32_t m;
    cli();  // Disable interrupts for atomic read
    m = millis_counter;
    sei();
    return m;
}