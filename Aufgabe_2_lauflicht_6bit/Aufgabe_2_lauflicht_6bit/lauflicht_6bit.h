/*
 *  Author: Broecker, Goel, Seus
 */


#ifndef LAUFLICHT_6_BIT_H_
#define LAUFLICHT_6_BIT_H_

#define F_CPU 16000000

#define TIME_DELAY		500
#define NUMBER_OF_PINS	1
#define END_VALUE		32
#define START_VALUE		1


void lauflicht_6bit_init();
void lauflicht_6bit_loop();


#endif /* LAUFLICHT_6_BIT_H_ */