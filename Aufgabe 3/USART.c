<<<<<<< HEAD
/*
 * USART.c
 *
 * Created: 25.04.2020 11:47:45
 *  Author: MariusAlexander
 */

#include "USART.h"

 void usart_init()
 {
	 UBRR0H  = (MYUBRR << 8);
	 UBRR0L  = MYUBRR;
 
	 UCSR0B |= (1 << RXEN0) | (1 << TXEN0);		// enable receiver and transmitter
	 UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);	// set frame 8data, 1stp
 }

 void usart_send(uint8_t data)
 {
	 while (!(UCSR0A & (1 << UDRE0)));
	 
	 UDR0 = data;
 }

 void usart_send_string(char* data)
 {
	 for (int i = 0; ; i++)
	 {
		 if (data[i] == 0)
		 {
			 break;
		 }
		 
		 usart_send(data[i]);
	 }
 }

 uint8_t usart_receive()
 {
	 while (!(UCSR0A & (1 << RXC0)));
	 
	 return (uint8_t) UDR0;
 }
=======
/*
 * USART.c
 *
 * Created: 25.04.2020 11:47:45
 *  Author: MariusAlexander
 */

#include "USART.h"

 void usart_init()
 {
	 UBRR0H  = (MYUBRR << 8);
	 UBRR0L  = MYUBRR;
 
	 UCSR0B |= (1 << RXEN0) | (1 << TXEN0);		// enable receiver and transmitter
	 UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);	// set frame 8data, 1stp
 }

 void usart_send(uint8_t data)
 {
	 while (!(UCSR0A & (1 << UDRE0)));
	 
	 UDR0 = data;
 }

 void usart_send_string(char* data)
 {
	 for (int i = 0; ; i++)
	 {
		 if (data[i] == 0)
		 {
			 break;
		 }
		 
		 usart_send(data[i]);
	 }
 }

 uint8_t usart_receive()
 {
	 while (!(UCSR0A & (1 << RXC0)));
	 
	 return (uint8_t) UDR0;
 }
>>>>>>> 7cc467a441b39f675b7bc4b1c92c614ef451ddfd
