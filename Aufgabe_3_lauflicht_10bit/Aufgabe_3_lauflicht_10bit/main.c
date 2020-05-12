/*
 *  Author: Broecker, Goel, Seus
 */


#include "lauflicht_10bit.h"

/*
	Aufgabe 3:
	
	10-Bit Lauflicht. 2 Ports sind notwendig… gleicher Umfang wie Aufgabe 2
*/


int main(void) {
	lauflicht_10bit_init();
	
	while(1){
		lauflicht_10bit_loop();
	}
}



