/**
  * @file encoder.h
  * @author MJ
  * @date Nov 2025
  */

#ifndef ENCODER_H
#define ENCODER_H


/**
 * @brief auslesen von Kanal A
 * 
 * @return bool  liefert true wenn Kanal A high ist, sonst false
 */
bool givePinA();


/**
 * @brief auslesen von Kanal B
 * 
 * @return bool  liefert true wenn Kanal B high ist, sonst false
 */
bool givePinB();

/**
 * @brief auslesen von Kanälen A und B
 * 
 * @return char   liefert a,b,c oder d abhängig von den Kanälen A und B
 */
char getPhase();


/**
 * @brief bestimmt Laufrichtung
 *
 * @return int  liefert 0 wenn Laufrichtung rechts, 1 wenn Laufrichtung links, 2 wenn keine Bewegung und -1 bei fehler
 */
int getDirection();


/*
ließt die kanäle A und B, <-- woher bekommen wir die???????????????????????
wenn A=0 und B=0 dann phase a
wenn A=1 und B=0 dann phase b
wenn A=1 und B=1 dann phase c
wenn A=0 und B=1 dann phase c

phase
lastPhase

variable für richtung? 0 für vorwärts 1 für rückwärts? ist phase a zu a vorwärts?????????????????
a,b - 0
d,a - 0
a,d - 1
a,c - ERROR weil phase übersprungen
...


counter bei vorwärts +1 bei rückwärts -1



*/

#endif