#ifndef IR_H
#define IR_H

#include <avr/io.h>

// Mask for 5 IR sensors connected to PD0–PD4
#define SENSOR_MASK 0x1F

// Functions
void IR_Init(void);
uint8_t IR_Read(void);

#endif
