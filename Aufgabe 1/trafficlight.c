/*
 * trafficlight.c
 *
 * Created: 29.04.2020 14:25:16
 *  Author: MariusAlexander
 */ 

#include "lauflicht.h"

#include "custom_utilities.h"

/*
	Aufgabe 1:

	3 LED (3 farbig) Eine Ampelschaltung	-> Aufgaben/trafficlight.h
		Am Anfang 1000ms rot
		Dann 100ms Rot-Gelb
		Dann 1000 Grün
		Dann 100ms gelb
		Dann wdh
*/


// traffic_light
inline void loop()
{
	// 1000ms: red
	SET_PIN_HIGH(PORTB, PORTB4);
	_delay_ms(1000);
	
	// 100ms:  red + yellow
	SET_PIN_HIGH(PORTB, PORTB3);
	_delay_ms(100);
	
	// 1000ms: green
	SET_PIN_LOW(PORTB, PORTB4);
	SET_PIN_LOW(PORTB, PORTB3);
	SET_PIN_HIGH(PORTB, PORTB2);
	_delay_ms(1000);
	
	// 100ms:  red + yellow
	SET_PIN_LOW(PORTB, PORTB2);
	SET_PIN_HIGH(PORTB, PORTB3);
	_delay_ms(100);
	
	SET_PIN_LOW(PORTB, PORTB3);
}

int main()
{
	// -- Setup --
	
	SET_PIN_OUTPUT(DDRB, PORTB4);	// rot
	SET_PIN_OUTPUT(DDRB, PORTB3);	// gelb
	SET_PIN_OUTPUT(DDRB, PORTB2);	// grün
	
	// -- Loop --
	while (1)
	{
		loop();
	}
}
