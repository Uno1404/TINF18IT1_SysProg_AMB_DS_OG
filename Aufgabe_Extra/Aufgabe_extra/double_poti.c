/*
 *  Author: Broecker, Goel, Seus
 */

#include "double_poti.h"
#include "custom_utilities.h"
#include "USART.h"
#define X_PIN 1
#define Y_PIN 0
#include <avr/interrupt.h>

volatile int16_t ADC_X = 0;
volatile int16_t ADC_Y = 0;
volatile int Button_press = 0;

ISR(ADC_vect) {
	cli();
	if((ADMUX & 0x0F) == X_PIN) {
		ADC_X = ADCL | (ADCH << 8);
		ADMUX = (ADMUX & 0xF0) | Y_PIN;
	}
	else {
		ADC_Y = ADCL | (ADCH << 8);
		ADMUX = (ADMUX & 0xF0) | X_PIN;
	}
	sei();
}

ISR (INT0_vect) {
	// toggle on button press
	Button_press ^= 1;
}

ISR (TIMER0_COMPA_vect)		// timer overflow interrupt
{
	TOGGLE_PIN(PORTD, OUTPUT_PIN);	//Toggle OUTPUT_PIN
}

void init() {
	ADMUX = 0;
	// use AVcc as the reference
	SET_PIN_HIGH(ADMUX, REFS0);
		
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
	    
	SET_PIN_HIGH(EICRA, ISC00);     // set INT0 to trigger on ANY logic
	SET_PIN_HIGH(EIMSK, INT0);      // Turns on INT0

		
	// enable interrupts
	sei();

	// init serial
	usart_init();
}

void loop() {
	ADCmeasurement -= 512;
	
		
	}
	/*
	char buffer[10];
	itoa(ADCmeasurement, buffer, 10);
	if (step&1){
		usart_send_string("Poti 1:  ");
		usart_send_string(buffer);
		usart_send_string("\n\r");
	}
	else{
		usart_send_string("Poti 2:  ");
		usart_send_string(buffer);
		usart_send_string("\n\r");
		itoa(Button_press, buffer, 10);
		usart_send_string("\n\rButton: ");
		usart_send_string(buffer);
	}
	ADMUX ^= 1;
	step   = ADMUX;
	
	_delay_ms(TIME_DELAY);
}
*/