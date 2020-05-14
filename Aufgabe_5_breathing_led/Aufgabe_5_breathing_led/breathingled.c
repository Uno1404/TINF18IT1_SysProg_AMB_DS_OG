/*
 *  Author: Broecker, Goel, Seus
 */

#include "breathingled.h"

void startup() {
	//sets PD6 as output
	SET_PIN_OUTPUT(DDRD, OUTPUT_PIN);	
	
	//sets PWM to 0
	OCR0A = 0;

	//sets none-inverting Mode
	SET_PIN_HIGH(TCCR0A, COM0A1);
	
	//sets fast PWM Mode
	SET_PIN_HIGH(TCCR0A, WGM01);
	SET_PIN_HIGH(TCCR0A, WGM00);
	SET_PIN_HIGH(TCCR0A, WGM02);
	
	//sets prescaler to 8 and starts PWM
	SET_PIN_HIGH(TCCR0B, CS01);
}

void mainloop() {
	//turning on the LED
	for(int i = 0; i <= MAXI; i++){
		OCR0A = i;
		_delay_ms(DELAY_DURATION);
	}
	
	//turning off the LED
	for(int i = MAXI; i >= 0; i--){
		OCR0A = i;
		_delay_ms(DELAY_DURATION);
	}
}