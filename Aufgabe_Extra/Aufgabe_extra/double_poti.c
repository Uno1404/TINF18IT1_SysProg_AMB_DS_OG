/*
 *  Author: Broecker, Goel, Seus
 */

#include "double_poti.h"
#include "custom_utilities.h"
#include "USART.h"

volatile uint16_t ADCmeasurement = 0;
volatile int Button_press = 0;
uint8_t step = 0;

ISR(ADC_vect) {
	ADCmeasurement = ADCL | (ADCH << 8);
}

ISR (INT0_vect) {
	Button_press ^= 1;
}
 
void init() {
	ADMUX = 0;
	// use AVcc as the reference
	SET_PIN_HIGH(ADMUX, REFS0); 
	//SET_PIN_HIGH(ADMUX, ADLAR);
		
	// 128 prescale for 16Mhz
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

	//Button press
	SET_PIN_LOW(DDRD, DDD2);        // Clear the PD2 pin for PD2
	    
	SET_PIN_HIGH(PORTD, PORTD2);    // turn On the Pull-up for PD2
	    
	SET_PIN_HIGH(EICRA, ISC00);        // set INT0 to trigger on ANY logic
	SET_PIN_HIGH(EIMSK, INT0);        // Turns on INT0
		
	sei();

	usart_init();
}

void loop(){
	char buffer[10];
	itoa(ADCmeasurement, buffer, 10);
	if (step&1){
		usart_send_string("Poti 1:  ");
	}
	else{
		usart_send_string("Poti 2:  ");
	}
	usart_send_string(buffer);
	itoa(Button_press, buffer, 10);
	usart_send_string("\n\rButton: ");
	usart_send_string(buffer);
	usart_send_string("\n\r");
	ADMUX = ADMUX ^1;
	step = ADMUX;
	_delay_ms(TIME_DELAY);
}