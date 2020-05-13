/*
 *  Author: Broecker, Goel, Seus
 */


#ifndef poti_H_
#define poti_H_

#define F_CPU	16000000
#define FOSC	F_CPU
#define BAUD	9600
#define MYUBRR	FOSC/16/BAUD-1

#include "stdint.h"
#include <avr/interrupt.h>

void usart_init();

void usart_send(uint8_t data);

void usart_send_string(char* data);

uint8_t usart_receive();

void init();

void loop();

#endif /* poti_H_ */