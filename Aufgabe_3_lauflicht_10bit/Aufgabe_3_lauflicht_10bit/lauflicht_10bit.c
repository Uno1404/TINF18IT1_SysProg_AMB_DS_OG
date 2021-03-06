/*
 *  Author: Broecker, Goel, Seus
 */


#include "lauflicht_10bit.h"

#include "custom_utillities.h"

char direction = LEFT;

void lauflicht_10bit_init() {
	//DDRB = 0b00001111;
	SET_PIN_OUTPUT(DDRB, DDB3);
	SET_PIN_OUTPUT(DDRB, DDB2);
	SET_PIN_OUTPUT(DDRB, DDB1);
	SET_PIN_OUTPUT(DDRB, DDB0);
	
	//DDRD = 0b11111100;
	SET_PIN_OUTPUT(DDRD, DDD7);
	SET_PIN_OUTPUT(DDRD, DDD6);
	SET_PIN_OUTPUT(DDRD, DDD5);
	SET_PIN_OUTPUT(DDRD, DDD4);
	SET_PIN_OUTPUT(DDRD, DDD3);
	SET_PIN_OUTPUT(DDRD, DDD2);
	
	//initial state: Turn on the LED at the right border and set the floating direction to LEFT ('l')
	SET_PIN_HIGH(START_PORT, START_PIN);
}

void moveLeft() {
	//if PortB is 0, the light is at register d, and vice versa. (PortD can not be 0 because the least significant bit of it is a status bit which we may not change)
	if (PORTB == 0) {
		//after the bitshift we have to add 1 again to maintain the status of the lsb
		PORTD = (PORTD >> 1) + 1;
	}
	else if (PORTD == 1) {
		PORTB = PORTB >> 1;
	}
}

void moveRight() {
	if (PORTB == 0) {
		//when bitshifting to the left we first have to nullify the status bit, because we would shift it which would cause unexpected results. After shifting we add 1 again
		PORTD = ((PORTD-1) << 1) + 1;
	}
	else if (PORTD == 1) {
		PORTB = PORTB << 1;
	}
}

void lauflicht_10bit_loop() {
	_delay_ms(TIME_DELAY);
	//check if the left border is reached and change the direction to right
	if (BORDER_LEFT) {
		direction = RIGHT;
	}
	//change the direction to left if the right border is reached
	else if (BORDER_RIGHT) {
		direction = LEFT;
	}
	//check if transition state is reached. If so: toggle both of the Pins at the border between both of the registers
	else if (TRANSITION) {
		TOGGLE_PIN(PORTB, PORTB0);
		TOGGLE_PIN(PORTD, PORTD7);
		_delay_ms(TIME_DELAY);
	}
	//check the direction
	if (direction == LEFT) {
		moveLeft();
	}
	else if (direction == RIGHT) {
		moveRight();
	}
}
