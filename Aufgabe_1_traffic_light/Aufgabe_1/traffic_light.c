/*
 *  Author: Broecker, Goel, Seus
 */

#define F_CPU 16000000

#include "traffic_light.h"

#include "custom_utilities.h"



void traffic_light_init(){
	SET_PIN_OUTPUT(DDRB, RED);		// red
	SET_PIN_OUTPUT(DDRB, YELLOW);	// yellow
	SET_PIN_OUTPUT(DDRB, GREEN);	// green
}

void traffic_light_loop(){
	// 1000ms: red
	SET_PIN_HIGH(PORTB, RED);
	_delay_ms(TIME_RED);
	
	// 100ms:  red + yellow
	SET_PIN_HIGH(PORTB, YELLOW);
	_delay_ms(TIME_YELLOW);
	
	// 1000ms: green
	SET_PIN_LOW(PORTB, RED);
	SET_PIN_LOW(PORTB, YELLOW);
	SET_PIN_HIGH(PORTB, GREEN);
	_delay_ms(TIME_GREEN);
	
	// 100ms: yellow
	SET_PIN_LOW(PORTB, GREEN);
	SET_PIN_HIGH(PORTB, YELLOW);
	_delay_ms(TIME_YELLOW);
	
	SET_PIN_LOW(PORTB, YELLOW);
}