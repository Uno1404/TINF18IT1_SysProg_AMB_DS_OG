/*
 *  Author: Broecker, Goel, Seus
 */


#include "poti.h"
#include "custom_utilities.h"

volatile uint8_t ADCvalue;

ISR(ADC_vect) {
	ADCvalue = ADCL | (ADCH << 8);          // pushing around for 10 Bit
}

void usart_init() {
	 UBRR0H  = (MYUBRR << 8); //BEQUATSCHEN
	 UBRR0L  = MYUBRR; //BEQUATSCHEN
	 
	 SET_PIN_HIGH(UCSR0B, RXEN0); // enable receiver and transmitter
	 SET_PIN_HIGH(UCSR0B, TXEN0); // enable receiver and transmitter
	 SET_PIN_HIGH(UCSR0C, UCSZ01); // set frame 8data, 1stp
	 SET_PIN_HIGH(UCSR0C, UCSZ00); // set frame 8data, 1stp
	 //UCSR0B |= (1 << RXEN0) | (1 << TXEN0);		// enable receiver and transmitter
	 //UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);	// set frame 8data, 1stp
 }

void usart_send(uint8_t data) {
	while (!(UCSR0A & (1 << UDRE0))); //BEQUATSCHEN
	 
	UDR0 = data;
 }

void usart_send_string(char* data) {
	for (int i = 0; ; i++)
	{
		if (data[i] == 0)
		{
			break;
		}
		
		usart_send(data[i]);
	}
 }

uint8_t usart_receive() {
	 while (!(UCSR0A & (1 << RXC0))); //BEQUATSCHEN
	 
	 return (uint8_t) UDR0;
 }
 
void init() {
	ADMUX = 0;
	SET_PIN_HIGH(ADMUX, REFS0); // use AVcc as the reference
	//ADMUX |= (1 << REFS0);    // use AVcc as the reference

	SET_PIN_HIGH(ADCSRA, ADPS2); // 128 prescale for 16Mhz
	SET_PIN_HIGH(ADCSRA, ADPS1); // 128 prescale for 16Mhz
	SET_PIN_HIGH(ADCSRA, ADPS0); // 128 prescale for 16Mhz
	SET_PIN_HIGH(ADCSRA, ADATE); // Set ADC Auto Trigger Enable
	//ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 prescale for 16Mhz
	//ADCSRA |= (1 << ADATE);   // Set ADC Auto Trigger Enable
		
	ADCSRB = 0;               // 0 for free running mode

	SET_PIN_HIGH(ADCSRA, ADEN); // Enable the ADC
	SET_PIN_HIGH(ADCSRA, ADIE); // Enable Interrupts
	//ADCSRA |= (1 << ADEN);    // Enable the ADC
	//ADCSRA |= (1 << ADIE);    // Enable Interrupts

	SET_PIN_HIGH(ADCSRA, ADSC); // Start the ADC conversion
	//ADCSRA |= (1 << ADSC);    // Start the ADC conversion

	sei();

	usart_init();
}

void loop() {
	char buffer[10];
	itoa(ADCvalue, buffer, 10);
	usart_send_string("Poti 1:  ");
	usart_send_string(buffer);
	usart_send_string("\n\n");
	_delay_ms(500);
}