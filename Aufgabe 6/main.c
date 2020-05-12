#define F_CPU 16000000

#include <stdint.h>       // needed for uint8_t

#include <avr/interrupt.h>
#include "USART.h"


volatile uint8_t ADCvalue;    // Global variable, set to volatile if used with ISR


int main(void)
{
	ADMUX = 0;
	ADMUX |= (1 << REFS0);    // use AVcc as the reference

	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 prescale for 16Mhz
	ADCSRA |= (1 << ADATE);   // Set ADC Auto Trigger Enable
					
	ADCSRB = 0;               // 0 for free running mode

	ADCSRA |= (1 << ADEN);    // Enable the ADC
	ADCSRA |= (1 << ADIE);    // Enable Interrupts

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion

	sei();

	usart_init();
	while (1)
	{
		char buffer[10];
		itoa(ADCvalue, buffer, 10);
		usart_send_string("Poti 1:  ");
		usart_send_string(buffer);
		usart_send_string("\n\n");
		_delay_ms(500);
	}
}


ISR(ADC_vect)
{
	ADCvalue = ADCL | (ADCH << 8);          // pushing around for 10 Bit
}
