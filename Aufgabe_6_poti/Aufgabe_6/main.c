/*
 *  Author: Broecker, Goel, Seus
 */

#include "poti.h"

/*
	Aufgabe 6:

	Ausgabe auf 10 Bit mit Poti
*/

int main(void) {
	analog_init();

    while (1) {
		analog_loop();
    }
}