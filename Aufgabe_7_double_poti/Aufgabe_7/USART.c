/*
 *  Author: Broecker, Goel, Seus
 */

#include "USART.h"
#include "custom_utilities.h"


void usart_init() {
	UBRR0H  = (MYUBRR << 8);
	UBRR0L  =  MYUBRR;

	// enable receiver and transmitter
	SET_PIN_HIGH(UCSR0B, RXEN0);	
	SET_PIN_HIGH(UCSR0B, TXEN0);

	// set frame 8data, 1stp
	SET_PIN_HIGH(UCSR0C, UCSZ01);	
	SET_PIN_HIGH(UCSR0C, UCSZ00);
}

void usart_send(uint8_t data) {
	while (!(UCSR0A & (1 << UDRE0)));
	
	UDR0 = data;
}

void usart_send_string(char* data) {
	for (int i = 0; ; i++) {
		if (data[i] == 0) {
			break;
		}
		
		usart_send(data[i]);
	}
}

uint8_t usart_receive() {
	while (!(UCSR0A & (1 << RXC0)));
	
	return (uint8_t) UDR0;
}