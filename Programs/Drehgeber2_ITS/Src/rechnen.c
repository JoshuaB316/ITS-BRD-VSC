/** 
* @file rechnen.c
* @author Esmat Rabaki, Raphael Pfeiffer
* @brief hier wird die Drehwinkel und Drehgeschwindigkeit berechnet
*/

#include "rechnen.h"
#include <stdint.h>


#define PROUMDREHUNG 1200.0


/**             
* @brief Berechnet den Drehwinkel basierend auf der Schrittzahl.
* @param schritte Die aktuelle Schrittzahl des Drehgebers.
* @return Der berechnete Drehwinkel in Grad.
*/
double berechneWinkel(uint32_t schritte)
{
     double schritteProUmdrehung = PROUMDREHUNG; 
     double drehwinkel = (schritte / schritteProUmdrehung) * 360.0;

    return drehwinkel;
}       


/**
* @brief Berechnet die Drehgeschwindigkeit basierend auf der Änderung der Schrittzahl und der Zeit.
* @param letzterWinkel Der vorherige Winkel.
* @param aktuellerWinkel Der aktuelle Winkel.
* @param alterZeit Die Startzeit in Millisekunden.
* @param aktuellerZeit Die Endzeit in Millisekunden. 
* @return der berechnete GeschwindigkeitProSekunde   
*/
double berechneGeschwindigkeit(double letzterWinkel, double aktuellerWinkel, uint32_t alterZeit, uint32_t aktuellerZeit)
{
    double zeitSekunden = (aktuellerZeit - alterZeit) / 90000000.0; // Millisekunden in Sekunden umrechnen
    double winkel = aktuellerWinkel - letzterWinkel;
    double geschwindigkeitProSekunde = winkel / zeitSekunden;
    return geschwindigkeitProSekunde;
}