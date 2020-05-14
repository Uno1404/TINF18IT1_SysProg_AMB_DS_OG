/*
 *  Author: Broecker, Goel, Seus
 */


#ifndef poti_H_
#define poti_H_

#define F_CPU 16000000

#define STD_SPEED		2000	// free running speed
#define STD_HYSTERESE	10		// threshold to determine direction

#define X_PIN		1	// joystick X
#define Y_PIN		0	// joystick Y
#define PWM_PINS	6	// Count of PWM capable pins
#define PORTS		2	// Count of used PORTS 


void init();

void loop();

#endif /* poti_H_ */