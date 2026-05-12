/**
 * @file    input.h
 * @authors Mustafa Kocatürk, Joshua Beinert
 * @date    Mai 2026
 */

#include <stdbool.h>
#include <stdint.h>

#ifndef INPUT_H
#define INPUT_H

extern int currentPhase;
extern int lastPhase;
extern int direction;
extern uint32_t stepCounter;
extern bool errorOccurred;

/**
 * @brief Liest den Zustand von Pin A des Drehgebers aus.
 * @return true, wenn Pin A HIGH ist, sonst false.
 */

bool readPinA(void);


/**
 * @brief Liest den Zustand von Pin B des Drehgebers aus.
 * @return true, wenn Pin B HIGH ist, sonst false.
 */
bool readPinB(void);


/**
 * @brief Bestimmt die aktuelle Phase anhand der Eingangssignale
 * @param A Zustand von Pin A
 * @param B Zustand von Pin B
 * @return Die aktuelle Phase (0 = a, 1 = b, 2 = c, 3 = d), oder -1 bei Fehler.
 */
int determinePhase(bool A, bool B);

void readInitialInput();

/**
 * @brief verarbeitet die Eingangssignale des Drehgebers und aktualisiert die Zustände.
 */
void processInput();

#endif