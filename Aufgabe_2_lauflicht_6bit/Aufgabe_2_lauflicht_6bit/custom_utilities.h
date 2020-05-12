/*
 *  Author: Broecker, Goel, Seus
 */

#include <avr/io.h>
#include <util/delay.h>

#ifndef CUSTOM_UTILLITIES_H_
#define CUSTOM_UTILLITIES_H_

#define HIGH	1
#define LOW		0

// DDRy, PIN
#define SET_PIN_OUTPUT(BLOCK, PIN)	BLOCK |=  (HIGH << PIN)
#define SET_PIN_INPUT(BLOCK, PIN)	BLOCK &= ~(HIGH << PIN)

// PORTy, PIN
#define SET_PIN_HIGH(BLOCK, PIN)	BLOCK |=  (HIGH << PIN)
#define SET_PIN_LOW(BLOCK, PIN)		BLOCK &= ~(HIGH << PIN)
#define TOGGLE_PIN(BLOCK, PIN)		BLOCK ^=  (HIGH << PIN)

#endif /* CUSTOM_UTILLITIES_H_ */

/*	 
 * Overview
 *
 * -------------------------------------------------------------------------
 *
 * DDRy - Data Direction Register
 *  D := for digital pins seven to zero
 *  B := for digital pins thirteen to eight
 *  C := for analogue pins five to zero
 *
 * each bank contains 8 Bits:
 *  1 := Output
 *  0 := Input
 *
 * example: set digital 7-4 as outputs, 3-0 as input
 *  DDRD = B11110000; 
 *
 * -------------------------------------------------------------------------
 *
 * PORTy - Control Output of Ports
 
 * each bank contains 8 Bits:
 *  1 := 5v (HIGH)
 *  0 := 0v (LOW)
 *
 * example: set digital 4-7 to LOW, digital 3-0 to HIGH
 *  PORTD = B00001111;
 *
 * -------------------------------------------------------------------------
 *
 * PINy - Read State of Pin
 *
 * example: digital 4-7 are LOW, digital 3-0 are HIGH
 *  PIND = B00001111;
 *
 */