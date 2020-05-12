/*
 *  Author: Broecker, Goel, Seus
 */


#ifndef LAUFLICHT_6_BIT_H_
#define LAUFLICHT_6_BIT_H_

#define F_CPU 16000000

#define TIME_DELAY		500
#define NUMBER_OF_PINS	1	// must be od number (1, 3, 5, 7)
#define START_VALUE		1  	// = 0B00000001 (Pin 1)
#define END_VALUE		32	// = 0B00100000 (Pin 8)


void lauflicht_6bit_init();
void lauflicht_6bit_loop();


#endif /* LAUFLICHT_6_BIT_H_ */