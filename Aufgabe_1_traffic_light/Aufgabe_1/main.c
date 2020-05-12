/*
 *  Author: Broecker, Goel, Seus
 */

#include "traffic_light.h"

/*
	Aufgabe 1:

	3 LED (3 farbig) Eine Ampelschaltung	-> Aufgaben/trafficlight.h
		Am Anfang 1000ms rot
		Dann 100ms Rot-Gelb
		Dann 1000 Grün
		Dann 100ms gelb
		Dann wdh
*/

int main(){
	traffic_light_init();
	while (1)
	{
		traffic_light_loop();
	}
}
