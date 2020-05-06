#define F_CPU 16000000

#include <avr/io.h>
#include <stdint.h>       // needed for uint8_t

#include <avr/interrupt.h>
#include "USART.h"
#include <util/delay.h>


volatile uint8_t ADCvalue;    // Global variable, set to volatile if used with ISR
uint8_t step = 0;


int main(void)
{
	ADMUX = 1;
	ADMUX |= (1 << REFS0);    // use AVcc as the reference
	ADMUX |= (1 << ADLAR);    // Right adjust for 8 bit resolution

	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 prescale for 16Mhz
	ADCSRA |= (1 << ADATE);   // Set ADC Auto Trigger Enable
					
	ADCSRB = 0;               // 0 for free running mode

	ADCSRA |= (1 << ADEN);    // Enable the ADC
	ADCSRA |= (1 << ADIE);    // Enable Interrupts

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion

	sei();    // Thanks N, forgot this the first time =P

	usart_init();
	while (1)
	{
		char buffer[10];
		itoa(ADCvalue, buffer, 10);
		if (step&1){
			usart_send_string("Poti 1:  ");
		}
		else{
			usart_send_string("Poti 2:  ");
		}
		usart_send_string(buffer);
		usart_send_string("\n\n");
		ADMUX = ADMUX ^1;
		step = ADMUX;
		_delay_ms(500);
	}
}


ISR(ADC_vect)
{
	
	ADCvalue = ADCH;          // only need to read the high value for 8 bit
	// REMEMBER: once ADCH is read the ADC will update
	
	// if you need the value of ADCH in multiple spots, read it into a register
	// and use the register and not the ADCH

}
