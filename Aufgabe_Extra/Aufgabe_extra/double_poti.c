/*
 *  Author: Broecker, Goel, Seus
 */

#include "double_poti.h"
#include "custom_utilities.h"
#include "USART.h"

#define STD_SPEED 2000
#define STD_HYSTERESE 10
#define X_PIN 1
#define Y_PIN 0
#define PWM_PINS 6

#include <avr/interrupt.h>
	
volatile int16_t ADC_X = 0;
volatile int16_t ADC_Y = 0;
volatile bool do_it = true;
uint8_t burning_led = 0;
bool direction_right = true;
uint16_t offCounter = 5;
uint16_t budget = 200;
volatile uint16_t percent = 10;
uint16_t counter = 0;

typedef struct{
	volatile uint8_t* destination_port;
	volatile uint8_t  portBits;
} PORT_CONTAINER;

typedef struct {
	PORT_CONTAINER* targetPortContainer;
	uint8_t bit_in_register;
	bool active;
} PIN;
	


PIN pins[PWM_PINS];
PORT_CONTAINER portContainerArray[2];

inline void set_pin(uint8_t id, uint8_t level, bool checkForIsActive) {
	PIN* target_pin = pins+id;
	if(level == HIGH) {
		target_pin->targetPortContainer->portBits |= (target_pin->bit_in_register);
	}
	else  {
		target_pin->targetPortContainer->portBits &= ~(target_pin->bit_in_register);
	}
}

inline void set_pin_active(uint8_t id, bool is_active) {
	PIN* target_pin = pins+id;
	target_pin->active = is_active;
	set_pin(id, (is_active?HIGH:LOW), false);
}

void pwm_pins_init() {
	
	uint16_t time = 0x01FF;
	OCR1A = (uint8_t) time;
	OCR1B = (uint8_t)(time >> 8);
	
	//set timer mode to CTC
	SET_PIN_HIGH(TCCR1A, WGM11);

	//Set the ISR COMPA vect
	SET_PIN_HIGH(TIMSK1, OCIE1A);

	//set prescaler to 0 and start timer
	SET_PIN_HIGH(TCCR1B, CS10);
	
	portContainerArray[0].destination_port = &PORTD;
	portContainerArray[0].portBits = 0x00;
	portContainerArray[1].destination_port = &PORTB;
	portContainerArray[1].portBits = 0x00;

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
	
	DDRD |= 0b01101000;
	DDRB |= 0b00001110;
	
	for (int i = 0; i < PWM_PINS; ++i) {
		set_pin_active(i, false);
	}

	set_pin_active(0, true);
}

ISR(ADC_vect) {
	if((ADMUX & 0x0F) == X_PIN) {
		ADC_X = (ADCL | (ADCH << 8)) - 512;
		ADMUX = (ADMUX & 0xF0) | Y_PIN;
	}
	else {
		ADC_Y = (ADCL | (ADCH << 8));
		percent = ADC_Y / 5;
		ADMUX = (ADMUX & 0xF0) | X_PIN;
	}
}


ISR (TIMER1_COMPA_vect)	{	// timer overflow interrupt
	//percent = ADC_Y / 5;
	counter++;
	if(counter >= budget)
		counter = 0;
	uint8_t targetMode = (counter >= percent) ? LOW:HIGH;	
	for(uint8_t i = 0; i < 2; ++i) {
		if(targetMode == HIGH){
			*portContainerArray[i].destination_port = portContainerArray[i].portBits;			
		}
		else{
			*portContainerArray[i].destination_port &= ~(portContainerArray[i].portBits);
		}
	}
}

void analog_init() {	
	ADMUX = 5;
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
}

void init() {
	// analog init
	analog_init();
	
	// init pwm
	pwm_pins_init();	

	// init serial
	usart_init();
	
	// enable interrupts
	sei();
}

void delay(uint16_t ms) {
	for(uint16_t i = 0; i < ms; ++i) {
		_delay_ms(1);
	} 	
}

void loop() {
	uint16_t speed;
	if (ADC_X < -STD_HYSTERESE) {
		direction_right = false;
		speed = -STD_SPEED/(ADC_X/10);
	}
	else if (ADC_X > STD_HYSTERESE) {
		direction_right = true;
		speed = STD_SPEED/(ADC_X/10);
	}
	else {
		speed = STD_SPEED;
	}
	set_pin_active(burning_led, false);
	if(direction_right) {
		burning_led = (burning_led+6-1)% 6;
	}
	else {
		burning_led = (burning_led+1)% 6;
	}
	set_pin_active(burning_led, true);
	delay(speed);
}