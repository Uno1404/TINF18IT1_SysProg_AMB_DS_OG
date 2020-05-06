/*
 * Kammerton.c
 *
 * Created: 01.05.2020 12:34:07
 *  Author: MariusAlexander
 */ 

#include "kammerton.h"

#include "custom_utilities.h"

#include <avr/interrupt.h>


ISR (INT0_vect)
{
	OCR0A = 120; // PWM for Kammerton C
}

ISR (INT1_vect)
{
	OCR0A = 70;  // PWM for Kammerton A
}

void main()
{
	// -- Setup --
	
	// -- PWM --
	// set pin 6 as output for the pwm
	SET_PIN_OUTPUT(DDRD, DDD6); 
	
	// PWM for Kammerton A
	OCR0A = 70;
	
	 // set none-inverting mode
	TCCR0A |= (1 << COM0A1);
	
	// set fast PWM Mode
	TCCR0A |= (1 << WGM01) | (1 << WGM00);
 	
	// set prescaler to 256 and starts PWM
	TCCR0B |= (1 << CS02);
	
	
	// -- Interrupts --
	DDRD &= ~(1 << DDD2);     // Clear the PD2 pin
	PORTD |= (1 << PORTD2);    // turn On the Pull-up
	
	DDRD &= ~(1 << DDD3);     // Clear the PD3 pin
	PORTD |= (1 << PORTD3);    // turn On the Pull-up
	
	EICRA |= (1 << ISC00);    // set INT0 to trigger on ANY logic change
	EICRA |= (1 << ISC10);    // set INT1 to trigger on ANY logic change
	EIMSK |= (1 << INT0);     // Turns on INT0
	EIMSK |= (1 << INT1);     // Turns on INT1

	// turn on interrupts
	sei();                    
	
	// -- Loop --
	while(1)
	{
		
	}
}