/**
 *******************************************************************
 * @file    input.h 
 * @author  Franz Korf
 *        	HAW-Hamburg
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @date    WS 2016
 * @brief   Header file of input module 
 *******************************************************************
*/

#ifndef _INPUT_H
#define _INPUT_H
#include <stdbool.h>

// This type defines the current phase, indendent of channel pins 
typedef enum {PhaseA = 0, PhaseB = 1, PhaseC = 2, PhaseD = 3} PhaseType;

/**
 *****************************************************************************************
 *  @brief   Diese Funktion initialisiert die Input Pins und deren Ports.
 *
 *  @return  Ist der Error-Reset-Button gedrueckt, liefert die Funktion true zurueck.
 *           Ansonsten false.
 ****************************************************************************************/
void initInput(void);

/**
 *****************************************************************************************
 *  @brief   Diese Funktion liefert den Status des Error-Reset-Buttons zurueck.
 *
 *  @return  Ist der Error-Reset-Button gedrueckt, liefert die Funktion true zurueck.
 *           Ansonsten false.
 ****************************************************************************************/
bool errorResetButtonPressed(void);

/**
 *****************************************************************************************
 *  @brief   Diese Funktion liefert die aktuellen Werte von Channel A und B zurueck.
 *
 *  @return  bit 0 == 1 <=> Channel B == high 
 *           bit 1 == 1 <=> Channel A == high
 bit 2 ... 7 : stets 0
 ****************************************************************************************/
PhaseType giveCurrentPhase(void); 

#endif
// EOF
