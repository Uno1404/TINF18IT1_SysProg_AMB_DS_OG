/*
 *  Author: Broecker, Goel, Seus
 */


#ifndef poti_H_
#define poti_H_

#define F_CPU	16000000
#define FOSC	F_CPU
#define BAUD	9600
#define MYUBRR	FOSC/16/BAUD-1
#include <stdbool.h>

#define TIME_DELAY 500

void init();

void loop();

#endif /* poti_H_ */