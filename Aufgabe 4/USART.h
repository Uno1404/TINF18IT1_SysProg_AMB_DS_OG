/*
 * USART.h
 *
 * Created: 25.04.2020 11:47:11
 *  Author: MariusAlexander
 */ 


#ifndef USART_H_
#define USART_H_


#define FOSC 16000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#include "avr/io.h"
#include "stdint.h"


void usart_init();

void usart_send(uint8_t data);

void usart_send_string(char* data);

uint8_t usart_receive();


#endif /* USART_H_ */