/*
 *  Author: Broecker, Goel, Seus
 */

#ifndef poti_H_
#define poti_H_

#define F_CPU		16000000

#include "custom_utilities.h"
#include <avr/interrupt.h>
#include <stdbool.h>

// DO NOT CHANGE
#define PWM_PINS						6		// Count of PWM capable pins
#define PORTS							2		// Count of used PORTS
#define Z_THRESHOLD						1000	// THRESHOLD FOR STOPPING
#define X_THRESHOLD						200		// THRESHOLD FOR CHANGING DIRECTION AND SPEED

// YOU MAY CHANGE
#define START_DIRECTION_RIGHT			true	// keep track of direction (true = right, false = left)
#define STD_SPEED						2000	// default speed
#define Y_PIN							0		// joystick Y
#define X_PIN							1		// joystick X
#define Z_PIN							5		// joystick Z
#define BRIGHTNESS_CONVERSION_FACTOR	4		// 10_TO_8_BITS_CONVERSION
#define STD_HYSTERESE					10		// threshold to determine direction
#define BUDGET							255		// total time for PWM
#define START_LED						0		// first led

void init();

void loop();

#endif /* poti_H_ */