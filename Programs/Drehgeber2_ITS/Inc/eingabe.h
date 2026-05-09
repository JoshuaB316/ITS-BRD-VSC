/** 
* @file eingabe.h
* @author Esmat Rabaki, Raphael Pfeiffer
* @brief hier wird die Kanal A und Kanal B eingelesen. dann wird 
* die phasenwechsel überprüft. 
*/

#include <stdbool.h>
#include <stdint.h>

#ifndef EINGABE_H
#define EINGABE_H

extern int aktuellePhase;
extern int letztePhase;
extern int richtung;
extern uint32_t schrittZaehler;
extern bool fehler;

/**
* @brief Liest den Zustand von Pin A des Drehgebers aus.
* @return true, wenn Pin A HIGH ist, sonst false.
*/

bool lesePinA(void);

/**
* @brief Liest den Zustand von Pin B des Drehgebers aus.
* @return true, wenn Pin B HIGH ist, sonst false.
*/
bool lesePinB(void);

/**
* @brief Bestimmt die aktuelle Phase anhand der Eingangssignale
* @param A Zustand von Pin A
* @param B Zustand von Pin B
* @return Die aktuelle Phase (0 = a, 1 = b, 2 = c, 3 = d), oder -1 bei Fehler.
*/
int bestimmePhase(bool A, bool B);

/**     
* @brief verarbeitet die Eingangssignale des Drehgebers und aktualisiert die Zustände.
* @return es wird entweder Fehler oder okay ausgegeben 
*/
void eingabeVerarbeitung(void); 


/**
* @brief Gibt die aktuelle Schrittzahl zurück.
* @return Die aktuelle Schrittzahl des Drehgebers.
*/
int gibSchrittzahl(void);

/** @brief Gibt den Fehlerstatus zurück.
*   @return true, wenn ein Fehler erkannt wurde, sonst false.
*/
bool gibFehler(void);

int gibPhase();
#endif 