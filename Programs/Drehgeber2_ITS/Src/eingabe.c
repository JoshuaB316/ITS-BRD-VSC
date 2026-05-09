/** 
* @file eingabe.c
* @author Esmat Rabaki, Raphael Pfeiffer
* @brief hier wird die Kanal A und Kanal B eingelesen. dann wird 
* die phasenwechsel überprüft. 
*/


#include "eingabe.h"
#include "stm32f429xx.h"
#include <stdbool.h>
#include <stdint.h>
#include "ausgabeLEDs.h"


// Definitionen für die Pin-Masken
#define IDR_MASK_PIN_0 (0x01U << (0))
#define IDR_MASK_PIN_1 (0x01U << (1))
#define ERROR -1
#define OK 0
//slkalskmjakl


// Globale Variablen für den Zustand des Drehgebers
int aktuellePhase = 0;        // 0 = a, 1 = b, 2 = c, 3 = d
int letztePhase = 0;
int richtung = 0;             // 1 = vorwärts, -1 = rückwärts, 0 = keine Änderung
uint32_t schrittZaehler = 0;  // Zählt die Phasenwechsel
bool fehler = false;          // Wird true, wenn ein ungültiger Übergang erkannt wird


/**
* @brief Liest den Zustand von Pin A des Drehgebers aus.
* @return true, wenn Pin A HIGH ist, sonst false.
*/
bool lesePinA(void)
{
    if (IDR_MASK_PIN_0 == (GPIOF->IDR & IDR_MASK_PIN_0)) {
        return true;
    } else {
        return false;
    } 
}

/**
* @brief Liest den Zustand von Pin B des Drehgebers aus.
* @return true, wenn Pin B HIGH ist, sonst false.
*/
bool lesePinB(void)
{
    if (IDR_MASK_PIN_1 == (GPIOF->IDR & IDR_MASK_PIN_1)) {
        return true;
    } else {
        return false;
    }
}

/**
* @brief Bestimmt die aktuelle Phase anhand der Eingangssignale.
* @param A Zustand von Pin A
* @param B Zustand von Pin B
* @return Die aktuelle Phase (0 = a, 1 = b, 2 = c, 3 = d) oder -1 bei Fehler.
*/
int bestimmePhase(bool A, bool B)
{
    if (!A && !B) return 0;   // Phase a
    if (A && !B)  return 1;   // Phase b
    if (A && B)   return 2;   // Phase c
    if (!A && B)  return 3;   // Phase d
    return ERROR;                // Fehler
}

/**     
* @brief verarbeitet die Eingangssignale des Drehgebers und aktualisiert die Zustände.
* @return es wird entweder Fehler oder okay ausgegeben 
*/
void eingabeVerarbeitung(void)
{       
    bool A = lesePinA();
    bool B = lesePinB();

    letztePhase = aktuellePhase;
    aktuellePhase = bestimmePhase(A, B);


    // Wenn Phase ungültig ist, Fehler setzen
    if (aktuellePhase == ERROR)
    {
        fehler = true;
    }
    // Keine Änderung → nichts tun
    if (letztePhase == aktuellePhase)
    {
         return;   // Beende die Funktion sofort.
    }


    // Phasenübergänge auswerten (nach Tabelle aus der Aufgabe)
    // Vorwärtsbewegung
    if (letztePhase == 0 && aktuellePhase == 1)
    {
        // a → b = Vorwärtsbewegung
        richtung = 1;
        schrittZaehler++;
    } 
    else if (letztePhase == 1 && aktuellePhase == 2) {
        // b → c = Vorwärtsbewegung
        richtung = 1;
        schrittZaehler++;
    }    
    else if (letztePhase == 2 && aktuellePhase == 3) {
        // c → d = Vorwärtsbewegung
        richtung = 1;
        schrittZaehler++;
    } 
    else if (letztePhase == 3 && aktuellePhase == 0) {
        richtung = 1;
        schrittZaehler++;
    }

    // Rückwärtsbewegung
    else if (letztePhase == 1 && aktuellePhase == 0) {
        // b → a = Rückwärtsbewegung
        richtung = -1;
        schrittZaehler--;
    } 
    else if (letztePhase == 2 && aktuellePhase == 1) {
        // c → b = Rückwärtsbewegung
        richtung = -1;
        schrittZaehler--;
    } 
    else if (letztePhase == 3 && aktuellePhase == 2) {
        // d → c = Rückwärtsbewegung
        richtung = -1;
        schrittZaehler--;
    } 
    else if (letztePhase == 0 && aktuellePhase == 3) {
        richtung = -1;
        schrittZaehler--;
    }
    
    else {
        // Alle anderen Übergänge sind ungültig
        fehler = true;
        toggle_LEDs_Error();
        // led 21 muss ausgehen
        return;
    }

    toggle_LEDs(schrittZaehler,richtung ); // Ausgabe der Schrittzahl auf die LEDs

}


/**         
* @brief Gibt die aktuelle Schrittzahl zurück.
* @return Die aktuelle Schrittzahl
*/  
int gibPhase(){

    return aktuellePhase;
}
int gibSchrittzahl(void)
{
    return schrittZaehler;
}


/**
* @brief Gibt an, ob ein Fehler im Drehgeber erkannt wurde.
* @return true, wenn ein Fehler erkannt wurde, sonst false.
*/
bool gibFehler(void)
{
    return fehler;
}


