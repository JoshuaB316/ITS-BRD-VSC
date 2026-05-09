/** 
* @file error.H
* @author Esmat Rabaki, Raphael Pfeiffer
* @brief hier wird der Fehlerzustand zurückgesetzt 
*/

#include "eingabe.h"
#include "ausgabeLEDs.h"


/**
*@brief hier werden alle veriablen zurückgesetzt
*/
void fehlerZuruecksetzen(void)
{
    fehler = false;        // Fehlerflag löschen
    richtung = 0;          // Richtung neutralisieren (optional)
    letztePhase = aktuellePhase; // Damit kein direkt neuer Fehler entsteht
    schrittZaehler=0;
    rest_LEDs_Error();


}

