/*
 *  Author: Broecker, Goel, Seus
 */


#ifndef KAMMERTON_H_
#define KAMMERTON_H_

// FORMULAR:	F_CPU / Prescaler / CompareValue (timer_interrupt) / 2 = Frequency

#define KAMMERTON_A		120
#define KAMMERTON_C		70

#define PRESCALER		256
#define OUTPUT_PIN		6


void kammerton();



#endif /* KAMMERTON_H_ */