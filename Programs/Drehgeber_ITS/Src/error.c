/**
 * @file    error.c
 * @authors Mustafa Kocatürk, Joshua Beinert
 * @date    Mai 2026
 */

#include "error.h"
#include "outputLEDs.h"
#include "input.h"

void errorReset() {
  // Alle Variablen zurücksetzen
  errorOccurred = false;
  direction = 0;
  lastPhase = currentPhase;
  stepCounter = 0;
  resetErrorLED();
}
