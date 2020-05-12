/*
 * util.h
 *
 * Created: 11.05.2020 19:59:48
 *  Author: goelo
 */ 


#ifndef UTIL_H_
#define UTIL_H_

#include <avr/io.h>
#include <util/delay.h>

#ifndef CUSTOM_UTILLITIES_H_
#define CUSTOM_UTILLITIES_H_

#define HIGH 1
#define LOW 0

#define SET_PIN_OUTPUT(BLOCK, PIN)	BLOCK |=  (1 << PIN)
#define SET_PIN_INPUT(BLOCK, PIN)	BLOCK &= ~(1 << PIN)

#define SET_PIN_HIGH(BLOCK, PIN)	BLOCK |=  (HIGH << PIN)
#define SET_PIN_LOW(BLOCK, PIN)		BLOCK &= ~(HIGH << PIN)
#define TOGGLE_PIN(BLOCK, PIN)		BLOCK ^=  (HIGH << PIN)

#endif /* UTIL_H_ */