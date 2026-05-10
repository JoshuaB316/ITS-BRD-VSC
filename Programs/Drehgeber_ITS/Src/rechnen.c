/**
 * @file rechnen.c
 * @authors Mustafa Kocatürk, Joshua Beinert
 * @date Mai 2026
 */

#include "rechnen.h"
#include <stdint.h>

#define PROUMDREHUNG 1200.0

double berechneWinkel(uint32_t schritte) {
  double schritteProUmdrehung = PROUMDREHUNG;
  double drehwinkel = (schritte / schritteProUmdrehung) * 360.0;

  return drehwinkel;
}

double berechneGeschwindigkeit(double letzterWinkel, double aktuellerWinkel,
                               uint32_t alterZeit, uint32_t aktuellerZeit) {
  double zeitSekunden = (aktuellerZeit - alterZeit) /
                        90000000.0; // Millisekunden in Sekunden umrechnen
  double winkel = aktuellerWinkel - letzterWinkel;
  double geschwindigkeitProSekunde = winkel / zeitSekunden;
  return geschwindigkeitProSekunde;
}