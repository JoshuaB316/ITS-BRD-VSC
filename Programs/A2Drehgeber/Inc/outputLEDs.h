/**
 * @file    outputLEDs.h
 * @authors Mustafa Kocatürk, Joshua Beinert
 * @date    Mai 2026
 */

#ifndef OUTPUTLEDS_H
#define OUTPUTLEDS_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Schaltet die LEDs entsprechend der übergebenen Maske ein oder aus.
 * @param led_mask Bitmaske, die angibt, welche LEDs geschaltet werden sollen.
 * @param richtung entweder 1(vorwärts) oder -1(rückwärts)
 */
void setLEDs(uint8_t led_mask, int richtung);


/**
 *@brief LED21 geht an, wenn es ein Fehler gibt
 */
void setErrorLED();


/**
 *@brief LED21 geht wieder aus
 */
void resetErrorLED();


/**
 *@brief es wird überprüft, ob taster S6 gedrückt würde.
 */
bool readPinS6();

#endif