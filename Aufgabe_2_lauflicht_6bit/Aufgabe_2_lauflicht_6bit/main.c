/*
 *  Author: Broecker, Goel, Seus
 */

#include "lauflicht_6bit.h"

/*
	Aufgabe 2:

	6-Bit Lauflicht… freie Wahl bei Laufzeit. Licht läuft hin und her. Auch gerne mehrere auf einmal laufen lassen
*/


int main() {
	lauflicht_6bit_init();
	
	while (1) {
		lauflicht_6bit_loop();
	}
}