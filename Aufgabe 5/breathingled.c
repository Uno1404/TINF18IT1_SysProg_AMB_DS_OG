#define F_CPU 16000000UL
#define TO_BIT(var) (1 << var)
#define MAXI 255

#include <avr/io.h>
#include <util/delay.h>


void startup(){
	//sets PB1 as output
	DDRB |= TO_BIT(DDB1);
	
	//sets PWM to 0
	OCR1A = 0;

	//sets none-inverting Mode
	TCCR1A |= TO_BIT(COM0A1);
	
	//sets fast PWM Mode
	TCCR1A |= TO_BIT(WGM01) | TO_BIT(WGM00) | TO_BIT(WGM02);
	
	//sets prescaler to 8 and starts PWM
	TCCR1B |= TO_BIT(CS01);
}

void mainloop(){
	//turning on the LED
	for(int i = 0; i <= MAXI; i++){
		OCR1A = i;
		_delay_ms(10);
	}
	
	//turning off the LED
	for(int i = MAXI; i >= 0; i--){
		OCR1A = i;
		_delay_ms(10);
	}
}

int main(void){
	startup();
	
	while(1){
		mainloop();
	}
}
