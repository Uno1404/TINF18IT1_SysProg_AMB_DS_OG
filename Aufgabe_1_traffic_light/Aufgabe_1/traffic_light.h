/*
 *  Author: Broecker, Goel, Seus
 */

#ifndef TRAFFIC_LIGHT_H_
#define TRAFFIC_LIGHT_H_

#define GREEN 		PORTB2
#define YELLOW 		PORTB3
#define RED 		PORTB4

#define TIME_RED 	1000
#define TIME_YELLOW 100
#define TIME_GREEN 	1000


void traffic_light_init();
void traffic_light_loop();

#endif /* TRAFFIC_LIGHT_H_ */