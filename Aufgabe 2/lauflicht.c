/*
 * lauflicht.c
 *
 * Created: 29.04.2020 16:20:15
 *  Author: MariusAlexander
 */ 

#include "lauflicht.h"

#include "custom_utilities.h"


inline void loop()
{
	while (!(PORTB & 32))   // while Pin 13 is LOW
	{
		_delay_ms(500);
	
		PORTB <<= 1;		// shift the HIGH state to the left
	}
	while (!(PORTB & 1))	// while PIN 8 is LOW
	{
		_delay_ms(500);

		PORTB >>= 1;		// shift the HIGH state to the left
	}
}

int main()
{
	// -- Setup --
	
	// one pin-bank is sufficient:
	DDRB  = 0B00111111;		// Declare pins 8-13 as output
	PORTB = 0B00000001;     // Set pin 8 to High
	
	// -- Loop --
	while (1)
	{
		loop();
	}
}