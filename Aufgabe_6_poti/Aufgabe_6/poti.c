/*
 *  Author: Broecker, Goel, Seus
 */

#include "poti.h"

#include "USART.h"
#include "custom_utilities.h"

volatile uint16_t ADCmeasurement;


ISR(ADC_vect) {	
	/*
		pushing around for 10 Bit
		to concat bits correctly
		ADCH		ADCL
		1111 1111   11
	*/
	ADCmeasurement = ADCL | (ADCH << 8);
}
 
void analog_init() { 
	// to read A0
	ADMUX = 0;

	// use AVcc as the reference
	SET_PIN_HIGH(ADMUX, REFS0);		
	
	// set prescaler to 128 for 16Mhz
	SET_PIN_HIGH(ADCSRA, ADPS2);
	SET_PIN_HIGH(ADCSRA, ADPS1);
	SET_PIN_HIGH(ADCSRA, ADPS0);

	// Set ADC Auto Trigger Enable
	SET_PIN_HIGH(ADCSRA, ADATE);
	
	// 0 for free running mode
	ADCSRB = 0;               

	// Enable the ADC
	SET_PIN_HIGH(ADCSRA, ADEN); 
	// Enable Interrupts
	SET_PIN_HIGH(ADCSRA, ADIE); 

	// Start the ADC conversion
	SET_PIN_HIGH(ADCSRA, ADSC); 

	// enable interrupts
	sei();

	// init serial
	usart_init();
}

void analog_loop() {
	// convert measurement to string
	char buffer[10];
	itoa(ADCmeasurement, buffer, 10);

	usart_send_string("Poti 1:  ");
	usart_send_string(buffer);
	usart_send_string("\n\r"); 

	_delay_ms(SERIAL_DELAY);
}