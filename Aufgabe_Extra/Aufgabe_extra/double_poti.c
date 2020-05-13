/*
 *  Author: Broecker, Goel, Seus
 */

#include "double_poti.h"
#include "custom_utilities.h"
#include "USART.h"
#define X_PIN 1
#define Y_PIN 0
#define PWM_PINS 6
#include <avr/interrupt.h>

volatile int16_t ADC_X = 0;
volatile int16_t ADC_Y = 0;
volatile int Button_press = 0;
uint8_t burning_led = 0;
bool direction_right = true;

typedef struct {
	volatile uint8_t* destination_port;
	uint8_t bit_in_register;
	bool active;
	} PIN;
	
PIN pins[PWM_PINS];

inline void set_pin(uint8_t id, uint8_t level) {
	PIN* target_pin = pins+id;
	if(level == HIGH) {
		*target_pin->destination_port |= (target_pin->bit_in_register);
	}
	else  {
		*target_pin->destination_port &= ~(target_pin->bit_in_register);
	}
}

inline void set_pin_active(uint8_t id, bool is_active) {
	PIN* target_pin = pins+id;
	target_pin->active = is_active;
	set_pin(id, (is_active?HIGH:LOW));
}

void pwm_pins_init() {
	pins[0].destination_port = &PORTD;
	pins[0].bit_in_register = (1 << PORTD3);
	pins[1].destination_port = &PORTD;
	pins[1].bit_in_register = (1 << PORTD5);
	pins[2].destination_port = &PORTD;
	pins[2].bit_in_register = (1 << PORTD6);
	pins[3].destination_port = &PORTB;
	pins[3].bit_in_register = (1 << PORTB1);
	pins[4].destination_port = &PORTB;
	pins[4].bit_in_register = (1 << PORTB2);
	pins[5].destination_port = &PORTB;
	pins[5].bit_in_register = (1 << PORTB3);
	DDRD |= 0b01101000;
	DDRB |= 0b00001110;
	for (int i = 0; i<PWM_PINS; i++) {
		set_pin_active(i, false);
	}
}



ISR(ADC_vect) {
	cli();
	if((ADMUX & 0x0F) == X_PIN) {
		ADC_X = (ADCL | (ADCH << 8)) - 512;
		ADMUX = (ADMUX & 0xF0) | Y_PIN;
	}
	else {
		ADC_Y = (ADCL | (ADCH << 8));
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
	cli();
	for(uint8_t i = 0; i<6; i++){
		PIN* target_pin = pins+i;
		if(target_pin->active) {
			*target_pin->destination_port ^= (target_pin->bit_in_register);
		}
	}
	sei();
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

	OCR0A = 50;
	
	//set timer mode to CTC
	TCCR0A |= (1 << WGM01);

	//Set the ISR COMPA vect
	TIMSK0 |= (1 << OCIE0A);

	//set prescaler to 256 and start timer
	TCCR0B |= (1 << CS02);
	/*	
	// set none-inverting mode
	SET_PIN_HIGH(TCCR0A, COM0A1);
		
	// set fast PWM Mode
	SET_PIN_HIGH(TCCR0A, WGM00);
	SET_PIN_HIGH(TCCR0A, WGM01);
	SET_PIN_HIGH(TCCR0A, WGM02);
		
	// set prescaler and start PWM
	//#if PRESCALER == 8			// set prescaler to 8
	SET_PIN_HIGH(TCCR0B, CS01);
	#elif PRESCALER == 64		// set prescaler to 64
	SET_PIN_HIGH(TCCR0B, CS00);
	SET_PIN_HIGH(TCCR0B, CS01);
	#elif PRESCALER == 256		// set prescaler to 256
	SET_PIN_HIGH(TCCR0B, CS02);
	#elif PRESCALER == 1024		// set prescaler to 1024
	SET_PIN_HIGH(TCCR0B, CS00);
	SET_PIN_HIGH(TCCR0B, CS02);
	#else
	# warning "PRESCALER not propperly defined (8-bit register -> possible PRESCALER values are 8, 64, 256, 1024)"
	#endif*/
	
	// enable interrupts
	sei();

	// init serial
	usart_init();
	// init pwm
	pwm_pins_init();
}

void delay(uint16_t ms){
	for(uint16_t i = 0; i<ms; i++) {
		_delay_ms(1);
	} 	
}

void loop() {
	OCR0A = ADC_Y/4;
	uint16_t speed;
	if (ADC_X<-5)
	{
		direction_right = false;
		speed = -2000/(ADC_X/10);
	}
	else if (ADC_X > 5)
	{
		direction_right = true;
		speed = 2000/(ADC_X/10);
	}
	else {
		speed = 2000;
	}
	set_pin_active(burning_led,false);
	if(direction_right){
		burning_led = (burning_led+6-1)% 6;
	}
	else{
		burning_led = (burning_led+1)% 6;
	}
	set_pin_active(burning_led,true);
	delay(speed);
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