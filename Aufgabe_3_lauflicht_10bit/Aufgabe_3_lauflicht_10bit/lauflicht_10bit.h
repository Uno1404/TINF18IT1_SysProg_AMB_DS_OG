/*
 *  Author: Broecker, Goel, Seus
 */

#ifndef _10BITLAUFLICHT_H_
#define _10BITLAUFLICHT_H_

#define F_CPU 16000000UL

//Keywords to describe the lights direction:
#define LEFT	'l'
#define RIGHT	'r'

#define START_PORT	PORTB
#define START_PIN	PORTB3

#define PIN_RIGHT	PORTD2
#define PIN_LEFT	PORTB3

//Macro to check if the right respectively the left Border is reached
#define BORDER_RIGHT	(PORTB ==  (1 << PIN_LEFT))
#define BORDER_LEFT		(PORTD == ((1 << PIN_RIGHT) + 1))

//Macro to determine if the transition state between register b and register d is reached
#define TRANSITION		((PORTB & 1) | (PORTD & (1 << 7)))


#define TIME_DELAY		100

void lauflicht_10bit_init();
void lauflicht_10bit_loop();


#endif /* 10BITLAUFLICHT_H_ */