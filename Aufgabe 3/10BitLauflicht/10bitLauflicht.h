#ifndef _10BITLAUFLICHT_H_
#define _10BITLAUFLICHT_H_

#define F_CPU 16000000
#include "custom_utillities.h"
//Keywords to describe the lights direction:
#define LEFT 'l'
#define RIGHT 'r'
//Macro to check if the right respectively the left Border is reached
#define BORDER_RIGHT (PORTB == (1 << 3))
#define BORDER_LEFT (PORTD == ((1 << 2)+1))
//Macro to determine if the transition state between register b and register d is reached
#define TRANSITION ((PORTB & 1) | (PORTD & (1 << 7)))
//function to start 10bitfloatinglight
#define START_PORT PORTB
#define START_NUMBER 3

void lauflicht_init();
void lauflicht();

#endif /* 10BITLAUFLICHT_H_ */