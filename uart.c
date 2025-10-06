#include "common.h"
#include "uart.h"

void UART_Init(void) {
	// Set baud rate (9600 for 16MHz)
	uint16_t ubrr = (F_CPU / (16UL * BAUD_RATE)) - 1;
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;
	
	// Enable receiver and transmitter
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	
	// Set frame format: 8 data bits, 1 stop bit, no parity
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void UART_Transmit(uint8_t data) {
	// Wait for empty transmit buffer
	while (!(UCSR0A & (1 << UDRE0)));
	// Put data into buffer
	UDR0 = data;
}

uint8_t UART_Receive(void) {
	// Wait for data to be received
	while (!(UCSR0A & (1 << RXC0)));
	// Get and return received data
	return UDR0;
}

void UART_SendString(const char* str) {
	while (*str) {
		UART_Transmit(*str++);
	}
}