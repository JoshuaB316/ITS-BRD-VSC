/**
 * @file error.c
 * @authors Mustafa Kocatürk, Joshua Beinert
 * @date Mai 2026
 */

#include "error.h"
#include "ausgabeLEDs.h"
#include "eingabe.h"

void errorReset(void) {
  // Alle Variablen zurücksetzen
  errorOccurred = false;
  direction = 0;
  lastPhase = currentPhase;
  stepCounter = 0;
  resetErrorLED();
}
