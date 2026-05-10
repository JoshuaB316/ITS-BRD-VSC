/**
 * @file error.c
 * @authors Mustafa Kocatürk, Joshua Beinert
 * @date Mai 2026
 */

#include "ausgabeLEDs.h"
#include "eingabe.h"

/**
 *@brief hier werden alle veriablen zurückgesetzt
 */
void fehlerZuruecksetzen(void) {
  fehler = false;              // Fehlerflag löschen
  richtung = 0;                // Richtung neutralisieren (optional)
  letztePhase = aktuellePhase; // Damit kein direkt neuer Fehler entsteht
  schrittZaehler = 0;
  rest_LEDs_Error();
}
