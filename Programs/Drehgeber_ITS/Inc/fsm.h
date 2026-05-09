/**
  * @file fsm.h
  * @author Franz Korf, HAW Hamburg 
  * @date April 2016
  * @brief Header of finite state machine module. 
  *        Die FSM verwaltet Phasewechsel, Drehrichtung und den Phasenzähler.     
  */
#ifndef _FSM_H
#define _FSM_H

#include <stdbool.h>
#include "input.h"
#include <stdint.h>

/**
 *****************************************************************************************
 *  @brief  Diese Funktion liefert die aktuaelle Anzahl der Phasenwechsel und 
 *          Beachtung der Drehrichtung.
 *
 *  @param  ts call by ref Parameter: Zeitstempel der letzten Änderungen von PhaseCount
 *
 *  @return Aktuelle Anzahl von Phasenwechseln
 ****************************************************************************************/
long int getPhaseCount(uint32_t *ts);

/**
 *****************************************************************************************
 *  @brief  Diese Funktion initialisiert die FSM.
 *
 *  @param  phase Die akuelle Phase, die von Kanal A und B gebildet wird.
 *
 *  @return none
 ****************************************************************************************/
void initFSM(PhaseType phase);

/**
 *****************************************************************************************
 *  @brief  Diese Funktion setzt die FSM zur¦ck (Fehlerzustand und Phasenz¦hler).
 *
 *  @return none
 ****************************************************************************************/
void resetFSM(void);


/**
 *****************************************************************************************
 *  @brief  Diese Funktion liefert den Fehlerstatus der FSM.
 *
 *  @return true <=> Mindestens ein Phasenwechsel wurde nicht erkannt.
 ****************************************************************************************/
bool inErrorState(void);

/**
 *****************************************************************************************
 *  @brief  Bei einer Vorwärtsdrehung liefert diese Funktion true zurück.
 *
 *  @return true <=> Der Drehgeber dreht sich vorwärts.
 ****************************************************************************************/
bool forwardRotation(void);

/**
 *****************************************************************************************
 *  @brief  Bei einer Rückwärtsdrehung liefert diese Funktion true zurück.
 *
 *  @return true <=> Der Drehgeber dreht sich rückwärts.
 ****************************************************************************************/
bool backwardRotation(void);

/**
 *****************************************************************************************
 *  @brief  Auf Basis der aktuellen Phase aktualisiert diese Funktion den Zustand der FSM.
 *
 *  @param  phase Die akuelle Phase, die von Kanal A und B gebildet wird.
 *
 *  @param  ts Zeitstempel der Beobachtung der aktuellen Phase.
 *
 *  @return none
 ****************************************************************************************/
void changeState(PhaseType phase, uint32_t ts);

#endif

// EOF
