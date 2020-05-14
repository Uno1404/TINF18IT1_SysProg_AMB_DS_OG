/*
 *  Author: Broecker, Goel, Seus
 */

#include "double_poti.h"

#include "custom_utilities.h"

#include <avr/interrupt.h>
#include <stdbool.h>

	
volatile int16_t ADC_X = 0;		// keep track of ADC measurement for the x-axis -> speed
volatile int16_t ADC_Y = 0;		// keep track of ADC measurement for the y-axis -> brightness

uint8_t burning_led = 0;		// keep track of the current active led
bool direction_right = true;	// keep track of direction (true = right, false = left)

volatile uint16_t percent = 10;	// on time for PWM
uint16_t budget	= 200;			// total time for PWM
uint16_t counter = 0;			// ticks

typedef struct {	
	volatile uint8_t* destination_port;		// address to PORTD or PORTB
	volatile uint8_t  portBits;				// state of the bits for PORTD and PORTB
} PORT_CONTAINER;	// byte cache for LED activation to access PORTB/D faster

typedef struct {
	PORT_CONTAINER* targetPortContainer;	// store information about the PORTB/D register
	uint8_t bit_in_register;				// pin number for the PORTB/D register
} PIN;

PIN pins[PWM_PINS];							// PWM Pins
PORT_CONTAINER portContainerArray[PORTS];	// PORTB and PORTD


/* sets the pin in the cache byte to HIGH or LOW
	id	  = pin number
	level = HIGH or LOW
*/
inline void set_pin_active(uint8_t id, bool state) {
	PIN* target_pin = pins + id;	// get the correct pin
	if (state) {
		target_pin->targetPortContainer->portBits |=  (target_pin->bit_in_register);	// sets the specified bit accordingly
	}
	else {
		target_pin->targetPortContainer->portBits &= ~(target_pin->bit_in_register);	// clears the specified bit accordingly
	}
}

/* inits pwm
   we use only one timer to turn the PWM capable pins on or off
*/
void pwm_pins_init() {	
	// set the timer
	uint16_t time = 0x01FF;			// 511
	// split up the 16 bit time variable to two 8 bit registers
	OCR1A = (uint8_t) time;			
	OCR1B = (uint8_t)(time >> 8);
	
	// set timer mode to CTC
	SET_PIN_HIGH(TCCR1A, WGM11);

	// set the ISR COMPA vect (interrupt)
	SET_PIN_HIGH(TIMSK1, OCIE1A);

	// set prescaler to 0 and start timer
	SET_PIN_HIGH(TCCR1B, CS10);
	
	// get addresses from ports
	portContainerArray[0].destination_port = &PORTD;
	portContainerArray[0].portBits = 0x00;
	portContainerArray[1].destination_port = &PORTB;
	portContainerArray[1].portBits = 0x00;

	// set pwm pins 
	pins[0].targetPortContainer = portContainerArray;
	pins[0].bit_in_register = (1 << PORTD3);
	pins[1].targetPortContainer = portContainerArray;
	pins[1].bit_in_register = (1 << PORTD5);
	pins[2].targetPortContainer = portContainerArray;
	pins[2].bit_in_register = (1 << PORTD6);
	pins[3].targetPortContainer = portContainerArray+1;
	pins[3].bit_in_register = (1 << PORTB1);
	pins[4].targetPortContainer = portContainerArray+1;
	pins[4].bit_in_register = (1 << PORTB2);
	pins[5].targetPortContainer = portContainerArray+1;
	pins[5].bit_in_register = (1 << PORTB3);
	
	// set the two Data Direction Registers accordingly
	DDRD |= 0b01101000;
	DDRB |= 0b00001110;
	
	// turn all LEDS off
	for (int i = 0; i < PWM_PINS; ++i) {
		set_pin_active(i, false);
	}
	
	// and set the first LED on
	set_pin_active(0, true);
}


// init analog stuff
void analog_init() {
	// A0
	ADMUX = 0;
	
	// use AVcc as the reference
	SET_PIN_HIGH(ADMUX, REFS0);
	
	// prescale to 128 for 16Mhz
	SET_PIN_HIGH(ADCSRA, ADPS2);
	SET_PIN_HIGH(ADCSRA, ADPS1);
	SET_PIN_HIGH(ADCSRA, ADPS0);

	// Set ADC Auto Trigger Enable
	SET_PIN_HIGH(ADCSRA, ADATE);
	
	// LOW (0) for free running mode
	ADCSRB = LOW;

	// Enable the ADC (Analog Device Converter)
	SET_PIN_HIGH(ADCSRA, ADEN);
	
	// Enable Interrupts
	SET_PIN_HIGH(ADCSRA, ADIE);

	// Start the ADC conversion
	SET_PIN_HIGH(ADCSRA, ADSC);
}

// Interrupt: Analog read
ISR(ADC_vect) {
	if ((ADMUX & 0x0F) == X_PIN) {			// if X_PIN was read
		ADC_X = (ADCL | (ADCH << 8)) - 512;	// set ADC_X and normalize it to 0 by subtracting 512 (middle pos = 0)
		ADMUX = (ADMUX & 0xF0) | Y_PIN;		// set ADMUX to PIN_Y
	}
	else {									// else Y_PIN was read
		ADC_Y = (ADCL | (ADCH << 8));		// set ADC_Y
		percent = ADC_Y / 5;				// scale the brightness
		ADMUX = (ADMUX & 0xF0) | X_PIN;		// set ADMUX to PIN_X
	}
}


// Interrupt: Timer overflow -> PWM 
ISR (TIMER1_COMPA_vect)	{
	counter++;
	if(counter >= budget)
		counter = 0;
	uint8_t targetMode = (counter >= percent) ? LOW:HIGH;
	for (uint8_t i = 0; i < PORTS; ++i) {	
		if(targetMode == HIGH) {
			*portContainerArray[i].destination_port = portContainerArray[i].portBits;		// sets the specified bit for the PORTB/D Register			
		}
		else {
			*portContainerArray[i].destination_port &= ~(portContainerArray[i].portBits);	// clears the specified bit for the PORTB/D Register
		}
	}
}

/* main init function
   inits PWM and analog
*/
void init() {
	// init analog 
	analog_init();
	
	// init pwm
	pwm_pins_init();
	
	// enable interrupts
	sei();
}

// helper function to simulate variable time delay
void delay(uint16_t ms) {
	for(uint16_t i = 0; i < ms; ++i) {
		_delay_ms(1);
	} 	
}


// main loop
void loop() {
	uint16_t speed;		// local speed variable 
	// determine direction and speed
	if (ADC_X < -STD_HYSTERESE) {
		direction_right = false;
		speed = -STD_SPEED / (ADC_X / STD_HYSTERESE);
	}
	else if (ADC_X > STD_HYSTERESE) {
		direction_right = true;
		speed =  STD_SPEED / (ADC_X / STD_HYSTERESE);
	}
	else { // if the measurement ADC_X is in between the threshold set speed to STD_SPEED
		speed =  STD_SPEED;
	}
	
	// disable the current LED
	set_pin_active(burning_led, false); 
	// determine the next LED
	if(direction_right) {
		burning_led = (burning_led + PWM_PINS - 1) % PWM_PINS;
	}
	else {
		burning_led = (burning_led + 1) % PWM_PINS;
	}
	// enable the current LED
	set_pin_active(burning_led, true);
	
	// simulate the speed
	delay(speed);
}