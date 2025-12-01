/**
  * @file encoder.h
  * @author MJ
  * @date Nov 2025
  */

#ifndef ENCODER_H
#define ENCODER_H
#include <stdbool.h>


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
int getPhase(bool A, bool B);


/**
 * @brief bestimmt Laufrichtung
 *
 * @return int  liefert 0 wenn Laufrichtung rechts, 1 wenn Laufrichtung links, 2 wenn keine Bewegung und -1 bei fehler
 */
int getDirection(int lastPhase, int currentPhase);




#endif