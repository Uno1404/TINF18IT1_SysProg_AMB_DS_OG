/*
 *  Author: Broecker, Goel, Seus
 */

#include "lauflicht_6bit.h"

#include "custom_utilities.h"



void lauflicht_6bit_init() {
	// one pin-bank is sufficient:
	DDRB  |= 0B00111111;				// Declare pins 8-13 as output
	PORTB |= NUMBER_OF_PINS;			// Set pin 8 to High		
}

void lauflicht_6bit_loop() {
	while (!(PORTB & END_VALUE)) {		// while Pin 13 is LOW
		_delay_ms(TIME_DELAY);
				
		PORTB <<= 1;					// shift the HIGH state to the left
	}
	while (!(PORTB & START_VALUE)) {	// while PIN 8 is LOW
		_delay_ms(TIME_DELAY);
		
		PORTB >>= 1;					// shift the HIGH state to the left
	}	
}

