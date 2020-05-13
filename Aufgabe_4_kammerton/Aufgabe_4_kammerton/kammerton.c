/*
 *  Author: Broecker, Goel, Seus
 */

#define F_CPU 16000000

#include "kammerton.h"

#include "custom_utilities.h"

#include <avr/interrupt.h>

	
ISR (INT0_vect) {
	OCR0A = KAMMERTON_C;	// PWM for Kammerton C
}

ISR (INT1_vect) {
	OCR0A = KAMMERTON_A;	// PWM for Kammerton A
}

ISR (TIMER0_COMPA_vect)		// timer overflow interrupt
{
	TOGGLE_PIN(PORTD, OUTPUT_PIN);	//Toggle OUTPUT_PIN
}

void kammerton() {
	// -- PWM --
	// set pin 6 as output for the pwm
	SET_PIN_OUTPUT(DDRD, OUTPUT_PIN);
	
	// PWM for Kammerton A
	OCR0A = KAMMERTON_A;
	
	// set none-inverting mode
	SET_PIN_HIGH(TCCR0A, COM0A1);
	
	// set fast PWM Mode
	SET_PIN_HIGH(TCCR0A, WGM00);
	SET_PIN_HIGH(TCCR0A, WGM01);
	SET_PIN_HIGH(TCCR0A, WGM02);
	
	// set prescaler and start PWM
	#if PRESCALER == 8			// set prescaler to 8
	SET_PIN_HIGH(TCCR0B, CS01);
	#elif PRESCALER == 64		// set prescaler to 64
	SET_PIN_HIGH(TCCR0B, CS00);
	SET_PIN_HIGH(TCCR0B, CS01);
	#elif PRESCALER == 256		// set prescaler to 256
	SET_PIN_HIGH(TCCR0B, CS02);
	#elif PRESCALER == 1024		// set prescaler to 1024
	SET_PIN_HIGH(TCCR0B, CS00);
	SET_PIN_HIGH(TCCR0B, CS02);
	#else
	# warning "PRESCALER not propperly defined (8-bit register -> possible PRESCALER values are 8, 64, 256, 1024)"
	#endif
	
	
	// -- Interrupts --
	SET_PIN_LOW(DDRD, DDD2);		// Clear the PD2 pin for PD2
	SET_PIN_LOW(DDRD, DDD3);		// Clear the PD3 pin for PD3
	
	SET_PIN_HIGH(PORTD, PORTD2);    // turn On the Pull-up for PD2
	SET_PIN_HIGH(PORTD, PORTD3);    // turn On the Pull-up for PD3
	
	SET_PIN_HIGH(EICRA, ISC00);			// set INT0 to trigger on ANY logic change
	SET_PIN_HIGH(EICRA, ISC10);			// set INT1 to trigger on ANY logic change
	SET_PIN_HIGH(EIMSK, INT0);			// Turns on INT0
	SET_PIN_HIGH(EIMSK, INT1);			// Turns on INT1

	// turn on interrupts
	sei();
}