#include "common.h"

#include "IR.h"

void IR_Init(void) {
	DDRC &= ~SENSOR_MASK;   // PD0–PD4 as input
	PORTC |= SENSOR_MASK;   // Enable pull-ups if needed
}

uint8_t IR_Read(void) {
	return (PINC & SENSOR_MASK);
}
