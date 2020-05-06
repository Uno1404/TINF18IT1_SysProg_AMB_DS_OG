<<<<<<< HEAD
/*
 * _10bitLauflicht.h
 *
 * Created: 01.05.2020 10:52:00
 *  Author: dseus
 */ 


#ifndef 10BITLAUFLICHT_H_
#define 10BITLAUFLICHT_H_

//Keywords to describe the lights direction:
#define LEFT 'l'
#define RIGHT 'r'
//Macro to check if the right respectively the left Border is reached
#define BORDER_RIGHT (PORTB == (1 << 3))
#define BORDER_LEFT (PORTD == ((1 << 2)+1))
//Macro to determine if the transition state between register b and register d is reached
#define TRANSITION ((PORTB & 1) | (PORTD & (1 << 7)))



=======
/*
 * _10bitLauflicht.h
 *
 * Created: 01.05.2020 10:52:00
 *  Author: dseus
 */ 


#ifndef 10BITLAUFLICHT_H_
#define 10BITLAUFLICHT_H_

//Keywords to describe the lights direction:
#define LEFT 'l'
#define RIGHT 'r'
//Macro to check if the right respectively the left Border is reached
#define BORDER_RIGHT (PORTB == (1 << 3))
#define BORDER_LEFT (PORTD == ((1 << 2)+1))
//Macro to determine if the transition state between register b and register d is reached
#define TRANSITION ((PORTB & 1) | (PORTD & (1 << 7)))



>>>>>>> 7cc467a441b39f675b7bc4b1c92c614ef451ddfd
#endif /* 10BITLAUFLICHT_H_ */