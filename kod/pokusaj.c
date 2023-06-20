/*
 * pokusaj.c
 *
 * Created: 19.6.2023. 15:44:18
 *  Author: jadra
 */ 

#include "AVR lib/AVR_lib.h"
#include "LCD/lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include "USART/USART.h"
#include "ADC/adc.h"

#define F_CPU 8000000ul

#define BAUDRATE 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUDRATE)) - 1)

void USART_Init(unsigned int ubrr) {
	// Set baud rate
	UBRRH = (unsigned char)(ubrr >> 8);
	UBRRL = (unsigned char)ubrr;

	// Enable receiver and transmitter
	UCSRB = (1 << RXEN) | (1 << TXEN);

	// Set frame format: 8 data bits, 1 stop bit
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}

void USART_Transmit(unsigned char data) {
	// Wait for empty transmit buffer
	while (!(UCSRA & (1 << UDRE)))
	;

	// Put data into buffer, sends the data
	UDR = data;
}

unsigned char USART_Receive() {
	// Wait for data to be received
	while (!(UCSRA & (1 << RXC)))
	;

	// Get and return received data from buffer
	return UDR;
}

int main() {
	USART_Init(UBRR_VALUE);

	_delay_ms(1000);

	while (1) {
		// Clear input buffer
		while (UCSRA & (1 << RXC))
		USART_Receive();

		USART_Transmit(0xFE);
		USART_Transmit(0x44);
		USART_Transmit(0x00);
		USART_Transmit(0x08);
		USART_Transmit(0x02);
		USART_Transmit(0x9F);
		USART_Transmit(0x25);

		_delay_ms(1000);

		unsigned char resp[7];
		for (int i = 0; i < 7; i++)
		resp[i] = USART_Receive();

		unsigned int high = resp[3];
		unsigned int low = resp[4];
		unsigned int co2 = (high << 8) | low;

		lcd_clrscr();
		lcd_home();
		lcd_print("%d",co2);
		_delay_ms(2000);
		// (You may need to configure the appropriate UART communication
		// for printing the value depending on your development environment)
	}

	return 0;
}
