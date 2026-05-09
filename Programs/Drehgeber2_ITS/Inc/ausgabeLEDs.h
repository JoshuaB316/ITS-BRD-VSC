/** 
* @file ausgabeLEDs.c
* @author Esmat Rabaki, Raphael Pfeiffer
* @brief hier werden die LEDS ausgegeben und Taster S6 wird überprüft 
*/
#ifndef AUSGABELEDS_H
#define AUSGABELEDS_H


#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Schaltet die LEDs entsprechend der übergebenen Maske ein oder aus.
 * @param led_mask Bitmaske, die angibt, welche LEDs geschaltet werden sollen.
 *@param richtung da wird entweder 1(vorwärts) oder -1(rückwärts) gegeben  
 */
void toggle_LEDs(uint32_t led_mask, int richtung);
/**
*@brief LED21 geht an, wenn es fehler bei der phasen auftreten
*/  
void toggle_LEDs_Error();

void rest_LEDs_Error();

/**
*@brief es wird überprüft, ob taster S6 gedrückt würde.
*
*/
bool readGPIOPIN ();

#endif 