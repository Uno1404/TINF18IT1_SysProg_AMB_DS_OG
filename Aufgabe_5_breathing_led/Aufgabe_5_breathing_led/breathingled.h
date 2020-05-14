/*
 *  Author: Broecker, Goel, Seus
 */


#ifndef BREATHINGLED_H_
#define BREATHINGLED_H_

#define F_CPU 16000000UL
#include "custom_utilities.h"

#define MAXI			255
#define DELAY_DURATION	10
#define OUTPUT_PIN		6

void startup();
void mainloop();

#endif /* BREATHINGLED_H_ */