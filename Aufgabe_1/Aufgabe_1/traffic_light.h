/*
 *  Author: Broecker, Goel, Seus
 */

#ifndef TRAFFIC_LIGHT_H_
#define TRAFFIC_LIGHT_H_

#define F_CPU 16000000
#include "custom_utilities.h"
#define GREEN PORTB2
#define YELLOW PORTB3
#define RED PORTB4
#define time_red 1000
#define time_yellow 100
#define time_green 1000

void traffic_light_init();
void traffic_light_loop();

#endif /* TRAFFIC_LIGHT_H_ */