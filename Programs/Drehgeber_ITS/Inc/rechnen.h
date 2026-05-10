/**
 * @file rechnen.h
 * @authors Mustafa Kocatürk, Joshua Beinert
 * @date Mai 2026
 */

#ifndef RECHNEN_H
#define RECHNEN_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Berechnet den Drehwinkel basierend auf der Schrittzahl.
 * @param schritte Anzahl der Schritte (Phasenwechsel)
 * @return Drehwinkel in Grad
 */
double calculateDegree(uint32_t schritte);

/**
 * @brief Berechnet die Drehgeschwindigkeit basierend auf der Änderung der
 * Schrittzahl und der Zeit.
 * @param letzterWinkel Der vorherige Winkel.
 * @param aktuellerWinkel Der aktuelle Winkel.
 * @param alterZeit Die Startzeit in Millisekunden.
 * @param aktuellerZeit Die Endzeit in Millisekunden.
 * @return der berechnete GeschwindigkeitProSekunde
 */
double calculateSpeed(double letzterWinkel, double aktuellerWinkel, uint32_t alterZeit, uint32_t aktuellerZeit);

#endif