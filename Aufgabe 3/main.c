/*
 * 10BitLauflicht.c
 *
 * Created: 29.04.2020 12:18:06
 * Author : dseus
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include "custom_utillities.h"
#include "USART.h"


int main(void)
{
    SET_PIN_OUTPUT(DDRB, 3);
	SET_PIN_OUTPUT(DDRB, 2);
	SET_PIN_OUTPUT(DDRB, 1);
	SET_PIN_OUTPUT(DDRB, 0);
	
	SET_PIN_OUTPUT(DDRD, 7);
	SET_PIN_OUTPUT(DDRD, 6);
	SET_PIN_OUTPUT(DDRD, 5);
	SET_PIN_OUTPUT(DDRD, 4);
	SET_PIN_OUTPUT(DDRD, 3);
	SET_PIN_OUTPUT(DDRD, 2);
	
	//initial state: Turn on the LED at the right border and set the floating direction to LEFT ('l')
	SET_PIN_HIGH(PORTB, 3);
	char direction = LEFT;
	
	while (1) {
		_delay_ms(50);
		//check if the left border is reached and change the direction to right
		if (BORDER_LEFT){
			direction = RIGHT;
		}
		//change the direction to left if the right border is reached
		else if (BORDER_RIGHT){
			direction = LEFT;
		}
		//check if transition state is reached. If so: toggle both of the Pins at the border between both of the registers
		else if (TRANSITION){
			TOGGLE_PIN(PORTB, 0);
			TOGGLE_PIN(PORTD,7);
			_delay_ms(50);
		}
		//check the direction
		if (direction == LEFT){
			//if PortB is 0, the light is at register d, and vice versa. (PortD can not be 0 because the least significant bit of it is a status bit which we may not change)
			if (PORTB == 0){
				//after the bitshift we have to add 1 again to maintain the status of the lsb
				PORTD = (PORTD >> 1) +1;
			}
			else if (PORTD == 1){
				PORTB = PORTB >> 1;
			}
		}
		else if (direction == RIGHT){
			if (PORTB == 0){
				//when bitshifting to the left we first have to nullify the status bit, because we would shift it which would cause unexpected results. After shifting we add 1 again
				PORTD = ((PORTD-1) << 1) +1;
			}
			else if (PORTD == 1){
				PORTB = PORTB << 1;
			}
		}
    }
}



