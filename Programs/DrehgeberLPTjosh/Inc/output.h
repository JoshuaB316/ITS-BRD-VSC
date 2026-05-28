/**
 * @file    output.h
 * @authors Mustafa Kocatürk, Joshua Beinert
 * @date    Mai 2026
 */


#ifndef OUTPUT_H
#define OUTPUT_H


/**
 * @brief Überschreibt immer eine der aktuellen Zahlen auf den ITS-Boardscreen für besseren performance
 */
void outputUpdate();


/**
 * @brief wandelt die double-Werte in Strings um für die Ausgabe auf dem Bildschirm
 * @param currentAngle
 * @param angleSpeed
 */
void outputChange(double currentAngle, double angleSpeed);

#endif